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
typedef  int /*<<< orphan*/  s_endian ;

/* Variables and functions */
#define  ELFDATA2LSB 130 
#define  ELFDATA2MSB 129 
#define  ELFDATANONE 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
elf_endian(unsigned int endian)
{
	static char s_endian[32];

	switch (endian) {
	case ELFDATANONE: return "none";
	case ELFDATA2LSB: return "2's complement, little endian";
	case ELFDATA2MSB: return "2's complement, big endian";
	default:
		snprintf(s_endian, sizeof(s_endian), "<unknown: %#x>", endian);
		return (s_endian);
	}
}