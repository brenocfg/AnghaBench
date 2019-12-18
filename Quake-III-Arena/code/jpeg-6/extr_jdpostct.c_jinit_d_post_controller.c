#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct jpeg_d_post_controller {int dummy; } ;
typedef  TYPE_3__* my_post_ptr ;
typedef  TYPE_4__* j_decompress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
typedef  scalar_t__ boolean ;
struct TYPE_10__ {int output_width; int out_color_components; TYPE_2__* mem; scalar_t__ output_height; scalar_t__ max_v_samp_factor; scalar_t__ quantize_colors; struct jpeg_d_post_controller* post; } ;
struct TYPE_7__ {int /*<<< orphan*/  start_pass; } ;
struct TYPE_9__ {scalar_t__ strip_height; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * whole_image; TYPE_1__ pub; } ;
struct TYPE_8__ {int /*<<< orphan*/ * (* alloc_sarray ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ;int /*<<< orphan*/ * (* request_virt_sarray ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ;scalar_t__ (* alloc_small ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  scalar_t__ JDIMENSION ;

/* Variables and functions */
 int /*<<< orphan*/  ERREXIT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  JERR_BAD_BUFFER_MODE ; 
 int /*<<< orphan*/  JPOOL_IMAGE ; 
 int /*<<< orphan*/  SIZEOF (int /*<<< orphan*/ ) ; 
 scalar_t__ jround_up (long,long) ; 
 int /*<<< orphan*/  my_post_controller ; 
 int /*<<< orphan*/  start_pass_dpost ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 

void
jinit_d_post_controller (j_decompress_ptr cinfo, boolean need_full_buffer)
{
  my_post_ptr post;

  post = (my_post_ptr)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				SIZEOF(my_post_controller));
  cinfo->post = (struct jpeg_d_post_controller *) post;
  post->pub.start_pass = start_pass_dpost;
  post->whole_image = NULL;	/* flag for no virtual arrays */
  post->buffer = NULL;		/* flag for no strip buffer */

  /* Create the quantization buffer, if needed */
  if (cinfo->quantize_colors) {
    /* The buffer strip height is max_v_samp_factor, which is typically
     * an efficient number of rows for upsampling to return.
     * (In the presence of output rescaling, we might want to be smarter?)
     */
    post->strip_height = (JDIMENSION) cinfo->max_v_samp_factor;
    if (need_full_buffer) {
      /* Two-pass color quantization: need full-image storage. */
      /* We round up the number of rows to a multiple of the strip height. */
#ifdef QUANT_2PASS_SUPPORTED
      post->whole_image = (*cinfo->mem->request_virt_sarray)
	((j_common_ptr) cinfo, JPOOL_IMAGE, FALSE,
	 cinfo->output_width * cinfo->out_color_components,
	 (JDIMENSION) jround_up((long) cinfo->output_height,
				(long) post->strip_height),
	 post->strip_height);
#else
      ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);
#endif /* QUANT_2PASS_SUPPORTED */
    } else {
      /* One-pass color quantization: just make a strip buffer. */
      post->buffer = (*cinfo->mem->alloc_sarray)
	((j_common_ptr) cinfo, JPOOL_IMAGE,
	 cinfo->output_width * cinfo->out_color_components,
	 post->strip_height);
    }
  }
}