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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  s_kind ;

/* Variables and functions */
#define  ODK_EXCEPTIONS 138 
#define  ODK_FILL 137 
#define  ODK_GP_GROUP 136 
#define  ODK_HWAND 135 
#define  ODK_HWOR 134 
#define  ODK_HWPATCH 133 
#define  ODK_IDENT 132 
#define  ODK_NULL 131 
#define  ODK_PAD 130 
#define  ODK_REGINFO 129 
#define  ODK_TAGS 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char *
option_kind(uint8_t kind)
{
	static char s_kind[32];

	switch (kind) {
	case ODK_NULL: return "NULL";
	case ODK_REGINFO: return "REGINFO";
	case ODK_EXCEPTIONS: return "EXCEPTIONS";
	case ODK_PAD: return "PAD";
	case ODK_HWPATCH: return "HWPATCH";
	case ODK_FILL: return "FILL";
	case ODK_TAGS: return "TAGS";
	case ODK_HWAND: return "HWAND";
	case ODK_HWOR: return "HWOR";
	case ODK_GP_GROUP: return "GP_GROUP";
	case ODK_IDENT: return "IDENT";
	default:
		snprintf(s_kind, sizeof(s_kind), "<unknown: %u>", kind);
		return (s_kind);
	}
}