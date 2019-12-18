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
typedef  int /*<<< orphan*/  s_data ;

/* Variables and functions */
#define  ELFDATA2LSB 130 
#define  ELFDATA2MSB 129 
#define  ELFDATANONE 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
elf_data_str(unsigned int data)
{
	static char s_data[32];

	switch (data) {
	case ELFDATANONE:	return "ELFDATANONE";
	case ELFDATA2LSB:	return "ELFDATA2LSB";
	case ELFDATA2MSB:	return "ELFDATA2MSB";
	}
	snprintf(s_data, sizeof(s_data), "<unknown: %#x>", data);
	return (s_data);
}