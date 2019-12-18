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
struct buffer {size_t len; size_t offset; size_t data; } ;

/* Variables and functions */
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (size_t,char const*,size_t) ; 

__attribute__((used)) static int query_peek(struct buffer buff, const char * data)
{
   size_t remain    = buff.len - buff.offset;
   size_t size_data = strlen(data);

   if (remain < size_data)
      return 0;

   return (strncmp(buff.data + buff.offset,
            data, size_data) == 0);
}