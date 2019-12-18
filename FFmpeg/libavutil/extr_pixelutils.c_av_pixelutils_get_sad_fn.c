#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sad ;
typedef  int /*<<< orphan*/ * av_pixelutils_sad_fn ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_pixelutils_sad_init_x86 (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ ** sad_c ; 

av_pixelutils_sad_fn av_pixelutils_get_sad_fn(int w_bits, int h_bits, int aligned, void *log_ctx)
{
#if !CONFIG_PIXELUTILS
    av_log(log_ctx, AV_LOG_ERROR, "pixelutils support is required "
           "but libavutil is not compiled with it\n");
    return NULL;
#else
    av_pixelutils_sad_fn sad[FF_ARRAY_ELEMS(sad_c)];

    memcpy(sad, sad_c, sizeof(sad));

    if (w_bits < 1 || w_bits > FF_ARRAY_ELEMS(sad) ||
        h_bits < 1 || h_bits > FF_ARRAY_ELEMS(sad))
        return NULL;
    if (w_bits != h_bits) // only squared sad for now
        return NULL;

#if ARCH_X86
    ff_pixelutils_sad_init_x86(sad, aligned);
#endif

    return sad[w_bits - 1];
#endif
}