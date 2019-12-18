#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tdesc_t ;
typedef  int iitype_t ;
struct TYPE_3__ {int ii_type; int /*<<< orphan*/ * ii_dtype; } ;
typedef  TYPE_1__ iidesc_t ;

/* Variables and functions */
 int II_GVAR ; 
 int II_NOT ; 
 int II_PSYM ; 
 int II_SVAR ; 
 int /*<<< orphan*/  expected (char*,char*,char*) ; 
 char* read_tid (char*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static iitype_t
parse_sym(char *cp, iidesc_t *ii)
{
	tdesc_t *tdp;
	iitype_t iitype = 0;

	/*
	 * name:G		global variable
	 * name:S		static variable
	 */
	switch (*cp++) {
	case 'G':
		iitype = II_GVAR;
		break;
	case 'S':
		iitype = II_SVAR;
		break;
	case 'p':
		iitype = II_PSYM;
		break;
	case '(':
		cp--;
		/*FALLTHROUGH*/
	case 'r':
	case 'V':
		iitype = II_NOT; /* not interesting */
		break;
	default:
		expected("parse_sym", "[GprSV(]", cp - 1);
	}

	if (!(cp = read_tid(cp, &tdp)))
		return (-1);

	ii->ii_type = iitype;
	ii->ii_dtype = tdp;

	return (iitype);
}