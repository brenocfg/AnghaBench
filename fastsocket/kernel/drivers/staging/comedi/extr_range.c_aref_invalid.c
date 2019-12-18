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
struct comedi_subdevice {int subdev_flags; } ;

/* Variables and functions */
#define  AREF_COMMON 131 
#define  AREF_DIFF 130 
#define  AREF_GROUND 129 
#define  AREF_OTHER 128 
 unsigned int CR_AREF (unsigned int) ; 
 int /*<<< orphan*/  DPRINTK (char*,unsigned int) ; 
 int SDF_COMMON ; 
 int SDF_DIFF ; 
 int SDF_GROUND ; 
 int SDF_OTHER ; 

__attribute__((used)) static int aref_invalid(struct comedi_subdevice *s, unsigned int chanspec)
{
	unsigned int aref;

	/*  disable reporting invalid arefs... maybe someday */
	return 0;

	aref = CR_AREF(chanspec);
	switch (aref) {
	case AREF_DIFF:
		if (s->subdev_flags & SDF_DIFF)
			return 0;
		break;
	case AREF_COMMON:
		if (s->subdev_flags & SDF_COMMON)
			return 0;
		break;
	case AREF_GROUND:
		if (s->subdev_flags & SDF_GROUND)
			return 0;
		break;
	case AREF_OTHER:
		if (s->subdev_flags & SDF_OTHER)
			return 0;
		break;
	default:
		break;
	}
	DPRINTK("subdevice does not support aref %i", aref);
	return 1;
}