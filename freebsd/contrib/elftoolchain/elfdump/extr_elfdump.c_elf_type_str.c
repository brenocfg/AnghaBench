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
#define  ET_CORE 132 
#define  ET_DYN 131 
#define  ET_EXEC 130 
 unsigned int ET_HIOS ; 
 unsigned int ET_LOOS ; 
 unsigned int ET_LOPROC ; 
#define  ET_NONE 129 
#define  ET_REL 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
elf_type_str(unsigned int type)
{
	static char s_type[32];

	switch (type)
	{
	case ET_NONE:	return "ET_NONE";
	case ET_REL:	return "ET_REL";
	case ET_EXEC:	return "ET_EXEC";
	case ET_DYN:	return "ET_DYN";
	case ET_CORE:	return "ET_CORE";
	}
	if (type >= ET_LOPROC)
		snprintf(s_type, sizeof(s_type), "<proc: %#x>", type);
	else if (type >= ET_LOOS && type <= ET_HIOS)
		snprintf(s_type, sizeof(s_type), "<os: %#x>", type);
	else
		snprintf(s_type, sizeof(s_type), "<unknown: %#x", type);
	return (s_type);
}