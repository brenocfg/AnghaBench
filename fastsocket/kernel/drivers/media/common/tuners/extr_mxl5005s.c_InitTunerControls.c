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
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXL5005_ControlInit (struct dvb_frontend*) ; 
 int /*<<< orphan*/  MXL5005_MXLControlInit (struct dvb_frontend*) ; 
 int /*<<< orphan*/  MXL5005_RegisterInit (struct dvb_frontend*) ; 

__attribute__((used)) static void InitTunerControls(struct dvb_frontend *fe)
{
	MXL5005_RegisterInit(fe);
	MXL5005_ControlInit(fe);
#ifdef _MXL_INTERNAL
	MXL5005_MXLControlInit(fe);
#endif
}