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
struct buffer {size_t offset; char* data; } ;

/* Variables and functions */
 scalar_t__ query_is_eot (struct buffer) ; 
 int /*<<< orphan*/  query_raise_unexpected_eof (size_t,char const**) ; 

__attribute__((used)) static struct buffer query_get_char(
      struct buffer buff, char * c,
      const char ** error)
{
   if (query_is_eot(buff))
   {
      query_raise_unexpected_eof(buff.offset, error);
      return buff;
   }

   *c = buff.data[buff.offset];
   buff.offset++;
   return buff;
}