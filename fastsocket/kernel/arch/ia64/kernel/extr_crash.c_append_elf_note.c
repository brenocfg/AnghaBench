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
struct elf_note {int n_namesz; size_t n_descsz; unsigned int n_type; } ;
typedef  int /*<<< orphan*/  Elf64_Word ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,size_t) ; 
 int strlen (char*) ; 

__attribute__((used)) static inline Elf64_Word
*append_elf_note(Elf64_Word *buf, char *name, unsigned type, void *data,
		size_t data_len)
{
	struct elf_note *note = (struct elf_note *)buf;
	note->n_namesz = strlen(name) + 1;
	note->n_descsz = data_len;
	note->n_type   = type;
	buf += (sizeof(*note) + 3)/4;
	memcpy(buf, name, note->n_namesz);
	buf += (note->n_namesz + 3)/4;
	memcpy(buf, data, data_len);
	buf += (data_len + 3)/4;
	return buf;
}