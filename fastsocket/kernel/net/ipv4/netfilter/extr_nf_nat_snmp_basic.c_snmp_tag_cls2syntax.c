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
struct snmp_cnv {int syntax; unsigned int tag; unsigned int class; } ;

/* Variables and functions */
 struct snmp_cnv* snmp_conv ; 

__attribute__((used)) static unsigned char snmp_tag_cls2syntax(unsigned int tag,
					 unsigned int cls,
					 unsigned short *syntax)
{
	const struct snmp_cnv *cnv;

	cnv = snmp_conv;

	while (cnv->syntax != -1) {
		if (cnv->tag == tag && cnv->class == cls) {
			*syntax = cnv->syntax;
			return 1;
		}
		cnv++;
	}
	return 0;
}