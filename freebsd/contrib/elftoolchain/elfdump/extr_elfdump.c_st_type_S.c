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
typedef  int /*<<< orphan*/  s_type ;

/* Variables and functions */
#define  STT_FILE 132 
#define  STT_FUNC 131 
#define  STT_NOTYPE 130 
#define  STT_OBJECT 129 
#define  STT_SECTION 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
st_type_S(unsigned int type)
{
	static char s_type[32];

	switch (type) {
	case STT_NOTYPE: return "NOTY";
	case STT_OBJECT: return "OBJT";
	case STT_FUNC: return "FUNC";
	case STT_SECTION: return "SECT";
	case STT_FILE: return "FILE";
	}
	snprintf(s_type, sizeof(s_type), "<unknown: %#x>", type);
	return (s_type);
}