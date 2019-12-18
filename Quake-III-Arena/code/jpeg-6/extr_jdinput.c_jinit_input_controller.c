#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct jpeg_input_controller {int dummy; } ;
typedef  TYPE_3__* my_inputctl_ptr ;
typedef  TYPE_4__* j_decompress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
struct TYPE_9__ {struct jpeg_input_controller* inputctl; TYPE_2__* mem; } ;
struct TYPE_6__ {void* eoi_reached; void* has_multiple_scans; int /*<<< orphan*/  finish_input_pass; int /*<<< orphan*/  start_input_pass; int /*<<< orphan*/  reset_input_controller; int /*<<< orphan*/  consume_input; } ;
struct TYPE_8__ {int /*<<< orphan*/  inheaders; TYPE_1__ pub; } ;
struct TYPE_7__ {scalar_t__ (* alloc_small ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  JPOOL_PERMANENT ; 
 int /*<<< orphan*/  SIZEOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  consume_markers ; 
 int /*<<< orphan*/  finish_input_pass ; 
 int /*<<< orphan*/  my_input_controller ; 
 int /*<<< orphan*/  reset_input_controller ; 
 int /*<<< orphan*/  start_input_pass ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
jinit_input_controller (j_decompress_ptr cinfo)
{
  my_inputctl_ptr inputctl;

  /* Create subobject in permanent pool */
  inputctl = (my_inputctl_ptr)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
				SIZEOF(my_input_controller));
  cinfo->inputctl = (struct jpeg_input_controller *) inputctl;
  /* Initialize method pointers */
  inputctl->pub.consume_input = consume_markers;
  inputctl->pub.reset_input_controller = reset_input_controller;
  inputctl->pub.start_input_pass = start_input_pass;
  inputctl->pub.finish_input_pass = finish_input_pass;
  /* Initialize state: can't use reset_input_controller since we don't
   * want to try to reset other modules yet.
   */
  inputctl->pub.has_multiple_scans = FALSE; /* "unknown" would be better */
  inputctl->pub.eoi_reached = FALSE;
  inputctl->inheaders = TRUE;
}