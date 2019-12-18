#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct GPU_FFT_TRANS {int dummy; } ;
struct GPU_FFT_COMPLEX {int re; int im; } ;
struct GPU_FFT {int dummy; } ;
typedef  int /*<<< orphan*/  bih ;
typedef  int /*<<< orphan*/  bfh ;
struct TYPE_5__ {int bfType; int bfSize; int bfOffBits; int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; int /*<<< orphan*/  biCompression; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ BITMAPINFOHEADER ;
typedef  TYPE_1__ BITMAPFILEHEADER ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  GPU_FFT_REV ; 
 struct GPU_FFT_COMPLEX* GPU_FFT_ROW (struct GPU_FFT*,int /*<<< orphan*/ ,int) ; 
 unsigned int Microseconds () ; 
 int N ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fputc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpu_fft_execute (struct GPU_FFT*) ; 
 int gpu_fft_prepare (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct GPU_FFT**) ; 
 int /*<<< orphan*/  gpu_fft_release (struct GPU_FFT*) ; 
 int /*<<< orphan*/  gpu_fft_trans_execute (struct GPU_FFT_TRANS*) ; 
 int gpu_fft_trans_prepare (int,struct GPU_FFT*,struct GPU_FFT*,struct GPU_FFT_TRANS**) ; 
 int /*<<< orphan*/  gpu_fft_trans_release (struct GPU_FFT_TRANS*) ; 
 int /*<<< orphan*/  in ; 
 int /*<<< orphan*/  log2_N ; 
 int mbox_open () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out ; 
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  usleep (int) ; 

int main(int argc, char *argv[]) {
    int x, y, ret, mb = mbox_open();
    unsigned t[4];

    struct GPU_FFT_COMPLEX *row;
    struct GPU_FFT_TRANS *trans;
    struct GPU_FFT *fft_pass[2];

    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;

    // Create Windows bitmap file
    FILE *fp = fopen("hello_fft_2d.bmp", "wb");
    if (!fp) return -666;

    // Write bitmap header
    memset(&bfh, 0, sizeof(bfh));
    bfh.bfType = 0x4D42; //"BM"
    bfh.bfSize = N*N*3;
    bfh.bfOffBits = sizeof(bfh) + sizeof(bih);
    fwrite(&bfh, sizeof(bfh), 1, fp);

    // Write bitmap info
    memset(&bih, 0, sizeof(bih));
    bih.biSize = sizeof(bih);
    bih.biWidth = N;
    bih.biHeight = N;
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bih.biCompression = BI_RGB;
    fwrite(&bih, sizeof(bih), 1, fp);

    // Prepare 1st FFT pass
    ret = gpu_fft_prepare(mb, log2_N, GPU_FFT_REV, N, fft_pass+0);
    if (ret) {
        return ret;
    }
    // Prepare 2nd FFT pass
    ret = gpu_fft_prepare(mb, log2_N, GPU_FFT_REV, N, fft_pass+1);
    if (ret) {
        gpu_fft_release(fft_pass[0]);
        return ret;
    }
    // Transpose from 1st pass output to 2nd pass input
    ret = gpu_fft_trans_prepare(mb, fft_pass[0], fft_pass[1], &trans);
    if (ret) {
        gpu_fft_release(fft_pass[0]);
        gpu_fft_release(fft_pass[1]);
        return ret;
    }

    // Clear input array
    for (y=0; y<N; y++) {
        row = GPU_FFT_ROW(fft_pass[0], in, y);
        for (x=0; x<N; x++) row[x].re = row[x].im = 0;
    }

    // Setup input data
    GPU_FFT_ROW(fft_pass[0], in,   2)[  2].re = 60;
    GPU_FFT_ROW(fft_pass[0], in, N-2)[N-2].re = 60;

    // ==> FFT() ==> T() ==> FFT() ==>
    usleep(1); /* yield to OS */   t[0] = Microseconds();
    gpu_fft_execute(fft_pass[0]);  t[1] = Microseconds();
    gpu_fft_trans_execute(trans);  t[2] = Microseconds();
    gpu_fft_execute(fft_pass[1]);  t[3] = Microseconds();

    // Write output to bmp file
    for (y=0; y<N; y++) {
        row = GPU_FFT_ROW(fft_pass[1], out, y);
        for (x=0; x<N; x++) {
            fputc(128+row[x].re, fp); // blue
            fputc(128+row[x].re, fp); // green
            fputc(128+row[x].re, fp); // red
        }
    }

    printf( "1st FFT   %6d usecs\n"
            "Transpose %6d usecs\n"
            "2nd FFT   %6d usecs\n",
            t[3]-t[2], t[2]-t[1], t[1]-t[0]);

    // Clean-up properly.  Videocore memory lost if not freed !
    gpu_fft_release(fft_pass[0]);
    gpu_fft_release(fft_pass[1]);
    gpu_fft_trans_release(trans);

    return 0;
}