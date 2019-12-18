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
struct uvd {int dummy; } ;
struct TYPE_2__ {int initialized; int camera_model; } ;

/* Variables and functions */
#define  IBMCAM_MODEL_1 131 
#define  IBMCAM_MODEL_2 130 
#define  IBMCAM_MODEL_3 129 
#define  IBMCAM_MODEL_4 128 
 TYPE_1__* IBMCAM_T (struct uvd*) ; 
 int ibmcam_model1_setup (struct uvd*) ; 
 int ibmcam_model2_setup (struct uvd*) ; 

__attribute__((used)) static int ibmcam_setup_on_open(struct uvd *uvd)
{
	int setup_ok = 0; /* Success by default */
	/* Send init sequence only once, it's large! */
	if (!IBMCAM_T(uvd)->initialized) { /* FIXME rename */
		switch (IBMCAM_T(uvd)->camera_model) {
		case IBMCAM_MODEL_1:
			setup_ok = ibmcam_model1_setup(uvd);
			break;
		case IBMCAM_MODEL_2:
			setup_ok = ibmcam_model2_setup(uvd);
			break;
		case IBMCAM_MODEL_3:
		case IBMCAM_MODEL_4:
			/* We do all setup when Isoc stream is requested */
			break;
		}
		IBMCAM_T(uvd)->initialized = (setup_ok != 0);
	}
	return setup_ok;
}