#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int cptr; unsigned int* uptr; int /*<<< orphan*/  fptr; scalar_t__ vptr; } ;
struct GPU_FFT_PTR {scalar_t__ vc; TYPE_1__ arm; } ;
struct GPU_FFT_BASE {scalar_t__ vc_msg; void* vc_code; void** vc_unifs; } ;
struct GPU_FFT {int x; int y; int in; int out; unsigned int step; } ;
typedef  int /*<<< orphan*/  COMPLEX ;

/* Variables and functions */
 int GPU_FFT_BUSY_WAIT_LIMIT ; 
 int GPU_FFT_QPUS ; 
 int gpu_fft_alloc (int,unsigned int,struct GPU_FFT_PTR*) ; 
 void* gpu_fft_ptr_inc (struct GPU_FFT_PTR*,int) ; 
 int /*<<< orphan*/  gpu_fft_shader_code (int) ; 
 unsigned int gpu_fft_shader_size (int) ; 
 int /*<<< orphan*/  gpu_fft_twiddle_data (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gpu_fft_twiddle_size (int,int*,int*,int*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 

int gpu_fft_prepare(
    int mb,         // mailbox file_desc
    int log2_N,     // log2(FFT_length) = 8...22
    int direction,  // GPU_FFT_FWD: fft(); GPU_FFT_REV: ifft()
    int jobs,       // number of transforms in batch
    struct GPU_FFT **fft) {

    unsigned info_bytes, twid_bytes, data_bytes, code_bytes, unif_bytes, mail_bytes;
    unsigned size, *uptr, vc_tw, vc_data;
    int i, q, shared, unique, passes, ret;

    struct GPU_FFT_BASE *base;
    struct GPU_FFT_PTR ptr;
    struct GPU_FFT *info;

    if (gpu_fft_twiddle_size(log2_N, &shared, &unique, &passes)) return -2;

    info_bytes = 4096;
    data_bytes = (1+((sizeof(COMPLEX)<<log2_N)|4095));
    code_bytes = gpu_fft_shader_size(log2_N);
    twid_bytes = sizeof(COMPLEX)*16*(shared+GPU_FFT_QPUS*unique);
    unif_bytes = sizeof(int)*GPU_FFT_QPUS*(5+jobs*2);
    mail_bytes = sizeof(int)*GPU_FFT_QPUS*2;

    size  = info_bytes +        // header
            data_bytes*jobs*2 + // ping-pong data, aligned
            code_bytes +        // shader, aligned
            twid_bytes +        // twiddles
            unif_bytes +        // uniforms
            mail_bytes;         // mailbox message

    ret = gpu_fft_alloc(mb, size, &ptr);
    if (ret) return ret;

    // Header
    info = (struct GPU_FFT *) ptr.arm.vptr;
    base = (struct GPU_FFT_BASE *) info;
    gpu_fft_ptr_inc(&ptr, info_bytes);

    // For transpose
    info->x = 1<<log2_N;
    info->y = jobs;

    // Ping-pong buffers leave results in or out of place
    info->in = info->out = ptr.arm.cptr;
    info->step = data_bytes / sizeof(COMPLEX);
    if (passes&1) info->out += info->step * jobs; // odd => out of place
    vc_data = gpu_fft_ptr_inc(&ptr, data_bytes*jobs*2);

    // Shader code
    memcpy(ptr.arm.vptr, gpu_fft_shader_code(log2_N), code_bytes);
    base->vc_code = gpu_fft_ptr_inc(&ptr, code_bytes);

    // Twiddles
    gpu_fft_twiddle_data(log2_N, direction, ptr.arm.fptr);
    vc_tw = gpu_fft_ptr_inc(&ptr, twid_bytes);

    uptr = ptr.arm.uptr;

    // Uniforms
    for (q=0; q<GPU_FFT_QPUS; q++) {
        *uptr++ = vc_tw;
        *uptr++ = vc_tw + sizeof(COMPLEX)*16*(shared + q*unique);
        *uptr++ = q;
        for (i=0; i<jobs; i++) {
            *uptr++ = vc_data + data_bytes*i;
            *uptr++ = vc_data + data_bytes*i + data_bytes*jobs;
        }
        *uptr++ = 0;
        *uptr++ = (q==0); // For mailbox: IRQ enable, master only

        base->vc_unifs[q] = gpu_fft_ptr_inc(&ptr, sizeof(int)*(5+jobs*2));
    }

    if ((jobs<<log2_N) <= GPU_FFT_BUSY_WAIT_LIMIT) {
        // Direct register poking with busy wait
        base->vc_msg = 0;
    }
    else {
        // Mailbox message
        for (q=0; q<GPU_FFT_QPUS; q++) {
            *uptr++ = base->vc_unifs[q];
            *uptr++ = base->vc_code;
        }

        base->vc_msg = ptr.vc;
    }

    *fft = info;
    return 0;
}