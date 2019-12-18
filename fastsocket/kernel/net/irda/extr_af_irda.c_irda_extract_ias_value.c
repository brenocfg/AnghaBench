#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t len; char* string; int /*<<< orphan*/  charset; } ;
struct TYPE_5__ {size_t len; char* octet_seq; } ;
struct TYPE_8__ {TYPE_3__ irda_attrib_string; TYPE_1__ irda_attrib_octet_seq; int /*<<< orphan*/  irda_attrib_int; } ;
struct irda_ias_set {int irda_attrib_type; TYPE_4__ attribute; } ;
struct TYPE_6__ {int /*<<< orphan*/  string; int /*<<< orphan*/  oct_seq; int /*<<< orphan*/  integer; } ;
struct ias_value {int type; size_t len; TYPE_2__ t; int /*<<< orphan*/  charset; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IAS_INTEGER 131 
#define  IAS_MISSING 130 
#define  IAS_OCT_SEQ 129 
#define  IAS_STRING 128 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int irda_extract_ias_value(struct irda_ias_set *ias_opt,
				  struct ias_value *ias_value)
{
	/* Look at the type */
	switch (ias_value->type) {
	case IAS_INTEGER:
		/* Copy the integer */
		ias_opt->attribute.irda_attrib_int = ias_value->t.integer;
		break;
	case IAS_OCT_SEQ:
		/* Set length */
		ias_opt->attribute.irda_attrib_octet_seq.len = ias_value->len;
		/* Copy over */
		memcpy(ias_opt->attribute.irda_attrib_octet_seq.octet_seq,
		       ias_value->t.oct_seq, ias_value->len);
		break;
	case IAS_STRING:
		/* Set length */
		ias_opt->attribute.irda_attrib_string.len = ias_value->len;
		ias_opt->attribute.irda_attrib_string.charset = ias_value->charset;
		/* Copy over */
		memcpy(ias_opt->attribute.irda_attrib_string.string,
		       ias_value->t.string, ias_value->len);
		/* NULL terminate the string (avoid troubles) */
		ias_opt->attribute.irda_attrib_string.string[ias_value->len] = '\0';
		break;
	case IAS_MISSING:
	default :
		return -EINVAL;
	}

	/* Copy type over */
	ias_opt->irda_attrib_type = ias_value->type;

	return 0;
}