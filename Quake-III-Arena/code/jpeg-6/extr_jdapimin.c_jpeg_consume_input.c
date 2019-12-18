#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* j_decompress_ptr ;
struct TYPE_13__ {int global_state; TYPE_2__* inputctl; TYPE_1__* src; } ;
struct TYPE_12__ {int (* consume_input ) (TYPE_3__*) ;int /*<<< orphan*/  (* reset_input_controller ) (TYPE_3__*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  (* init_source ) (TYPE_3__*) ;} ;

/* Variables and functions */
#define  DSTATE_BUFIMAGE 137 
#define  DSTATE_BUFPOST 136 
#define  DSTATE_INHEADER 135 
#define  DSTATE_PRELOAD 134 
#define  DSTATE_PRESCAN 133 
#define  DSTATE_RAW_OK 132 
#define  DSTATE_READY 131 
#define  DSTATE_SCANNING 130 
#define  DSTATE_START 129 
#define  DSTATE_STOPPING 128 
 int /*<<< orphan*/  ERREXIT1 (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JERR_BAD_STATE ; 
 int JPEG_REACHED_SOS ; 
 int JPEG_SUSPENDED ; 
 int /*<<< orphan*/  default_decompress_parms (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int stub3 (TYPE_3__*) ; 
 int stub4 (TYPE_3__*) ; 

int
jpeg_consume_input (j_decompress_ptr cinfo)
{
  int retcode = JPEG_SUSPENDED;

  /* NB: every possible DSTATE value should be listed in this switch */
  switch (cinfo->global_state) {
  case DSTATE_START:
    /* Start-of-datastream actions: reset appropriate modules */
    (*cinfo->inputctl->reset_input_controller) (cinfo);
    /* Initialize application's data source module */
    (*cinfo->src->init_source) (cinfo);
    cinfo->global_state = DSTATE_INHEADER;
    /*FALLTHROUGH*/
  case DSTATE_INHEADER:
    retcode = (*cinfo->inputctl->consume_input) (cinfo);
    if (retcode == JPEG_REACHED_SOS) { /* Found SOS, prepare to decompress */
      /* Set up default parameters based on header data */
      default_decompress_parms(cinfo);
      /* Set global state: ready for start_decompress */
      cinfo->global_state = DSTATE_READY;
    }
    break;
  case DSTATE_READY:
    /* Can't advance past first SOS until start_decompress is called */
    retcode = JPEG_REACHED_SOS;
    break;
  case DSTATE_PRELOAD:
  case DSTATE_PRESCAN:
  case DSTATE_SCANNING:
  case DSTATE_RAW_OK:
  case DSTATE_BUFIMAGE:
  case DSTATE_BUFPOST:
  case DSTATE_STOPPING:
    retcode = (*cinfo->inputctl->consume_input) (cinfo);
    break;
  default:
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);
  }
  return retcode;
}