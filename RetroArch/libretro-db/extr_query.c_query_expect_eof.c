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
struct buffer {size_t offset; unsigned int len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 struct buffer query_chomp (struct buffer) ; 
 int /*<<< orphan*/  query_raise_expected_eof (size_t,int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static struct buffer query_expect_eof(struct buffer buff, const char ** error)
{
   buff = query_chomp(buff);
   if ((unsigned)buff.offset < buff.len)
      query_raise_expected_eof(buff.offset, buff.data[buff.offset], error);
   return buff;
}