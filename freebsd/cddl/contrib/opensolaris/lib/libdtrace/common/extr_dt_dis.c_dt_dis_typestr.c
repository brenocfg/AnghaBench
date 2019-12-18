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
typedef  int /*<<< orphan*/  ulong_t ;
typedef  int /*<<< orphan*/  kind ;
struct TYPE_3__ {int dtdt_kind; int dtdt_ckind; int dtdt_flags; scalar_t__ dtdt_size; } ;
typedef  TYPE_1__ dtrace_diftype_t ;
typedef  int /*<<< orphan*/  ckind ;

/* Variables and functions */
#define  CTF_K_ARRAY 143 
#define  CTF_K_CONST 142 
#define  CTF_K_ENUM 141 
#define  CTF_K_FLOAT 140 
#define  CTF_K_FORWARD 139 
#define  CTF_K_FUNCTION 138 
#define  CTF_K_INTEGER 137 
#define  CTF_K_POINTER 136 
#define  CTF_K_RESTRICT 135 
#define  CTF_K_STRUCT 134 
#define  CTF_K_TYPEDEF 133 
#define  CTF_K_UNION 132 
#define  CTF_K_UNKNOWN 131 
#define  CTF_K_VOLATILE 130 
 int DIF_TF_BYREF ; 
 int DIF_TF_BYUREF ; 
#define  DIF_TYPE_CTF 129 
#define  DIF_TYPE_STRING 128 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static char *
dt_dis_typestr(const dtrace_diftype_t *t, char *buf, size_t len)
{
	char kind[16], ckind[16];

	switch (t->dtdt_kind) {
	case DIF_TYPE_CTF:
		(void) strcpy(kind, "D type");
		break;
	case DIF_TYPE_STRING:
		(void) strcpy(kind, "string");
		break;
	default:
		(void) snprintf(kind, sizeof (kind), "0x%x", t->dtdt_kind);
	}

	switch (t->dtdt_ckind) {
	case CTF_K_UNKNOWN:
		(void) strcpy(ckind, "unknown");
		break;
	case CTF_K_INTEGER:
		(void) strcpy(ckind, "integer");
		break;
	case CTF_K_FLOAT:
		(void) strcpy(ckind, "float");
		break;
	case CTF_K_POINTER:
		(void) strcpy(ckind, "pointer");
		break;
	case CTF_K_ARRAY:
		(void) strcpy(ckind, "array");
		break;
	case CTF_K_FUNCTION:
		(void) strcpy(ckind, "function");
		break;
	case CTF_K_STRUCT:
		(void) strcpy(ckind, "struct");
		break;
	case CTF_K_UNION:
		(void) strcpy(ckind, "union");
		break;
	case CTF_K_ENUM:
		(void) strcpy(ckind, "enum");
		break;
	case CTF_K_FORWARD:
		(void) strcpy(ckind, "forward");
		break;
	case CTF_K_TYPEDEF:
		(void) strcpy(ckind, "typedef");
		break;
	case CTF_K_VOLATILE:
		(void) strcpy(ckind, "volatile");
		break;
	case CTF_K_CONST:
		(void) strcpy(ckind, "const");
		break;
	case CTF_K_RESTRICT:
		(void) strcpy(ckind, "restrict");
		break;
	default:
		(void) snprintf(ckind, sizeof (ckind), "0x%x", t->dtdt_ckind);
	}

	if (t->dtdt_flags & (DIF_TF_BYREF | DIF_TF_BYUREF)) {
		(void) snprintf(buf, len, "%s (%s) by %sref (size %lu)",
		    kind, ckind, (t->dtdt_flags & DIF_TF_BYUREF) ? "user " : "",
		    (ulong_t)t->dtdt_size);
	} else {
		(void) snprintf(buf, len, "%s (%s) (size %lu)",
		    kind, ckind, (ulong_t)t->dtdt_size);
	}

	return (buf);
}