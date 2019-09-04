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
struct jpeg_decompress_struct {struct jpeg_decompress_struct* src; struct jpeg_decompress_struct* err; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct jpeg_decompress_struct*) ; 
 int /*<<< orphan*/  jpeg_destroy_decompress (struct jpeg_decompress_struct*) ; 

void _zbar_jpeg_decomp_destroy (struct jpeg_decompress_struct *cinfo)
{
    if(cinfo->err) {
        free(cinfo->err);
        cinfo->err = NULL;
    }
    if(cinfo->src) {
        free(cinfo->src);
        cinfo->src = NULL;
    }
    /* FIXME can this error? */
    jpeg_destroy_decompress(cinfo);
    free(cinfo);
}