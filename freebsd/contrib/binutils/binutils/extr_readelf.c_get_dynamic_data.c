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
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  byte_get (unsigned char*,unsigned int) ; 
 void* cmalloc (unsigned int,int) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 unsigned int fread (unsigned char*,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 

__attribute__((used)) static bfd_vma *
get_dynamic_data (FILE *file, unsigned int number, unsigned int ent_size)
{
  unsigned char *e_data;
  bfd_vma *i_data;

  e_data = cmalloc (number, ent_size);

  if (e_data == NULL)
    {
      error (_("Out of memory\n"));
      return NULL;
    }

  if (fread (e_data, ent_size, number, file) != number)
    {
      error (_("Unable to read in dynamic data\n"));
      return NULL;
    }

  i_data = cmalloc (number, sizeof (*i_data));

  if (i_data == NULL)
    {
      error (_("Out of memory\n"));
      free (e_data);
      return NULL;
    }

  while (number--)
    i_data[number] = byte_get (e_data + number * ent_size, ent_size);

  free (e_data);

  return i_data;
}