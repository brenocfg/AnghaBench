#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  abfd; } ;
typedef  TYPE_1__ common_header_type ;
typedef  scalar_t__ bfd_size_type ;

/* Variables and functions */
 char* bfd_alloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bfd_get_string (TYPE_1__*,char*,size_t) ; 
 size_t this_byte_and_next (TYPE_1__*) ; 

__attribute__((used)) static char *
read_id (common_header_type *ieee)
{
  size_t length;
  char *string;

  length = this_byte_and_next (ieee);
  if (length <= 0x7f)
    /* Simple string of length 0 to 127.  */
    ;

  else if (length == 0xde)
    /* Length is next byte, allowing 0..255.  */
    length = this_byte_and_next (ieee);

  else if (length == 0xdf)
    {
      /* Length is next two bytes, allowing 0..65535.  */
      length = this_byte_and_next (ieee);
      length = (length * 256) + this_byte_and_next (ieee);
    }

  /* Buy memory and read string.  */
  string = bfd_alloc (ieee->abfd, (bfd_size_type) length + 1);
  if (!string)
    return NULL;
  bfd_get_string (ieee, string, length);
  string[length] = 0;
  return string;
}