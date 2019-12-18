#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  int_; } ;
struct rmsgpack_dom_value {TYPE_1__ val; int /*<<< orphan*/  type; } ;
struct buffer {int offset; scalar_t__* data; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  RDT_INT ; 
 int /*<<< orphan*/  STRING_REP_INT64 ; 
 scalar_t__ isdigit (int) ; 
 int /*<<< orphan*/  query_raise_expected_number (int,char const**) ; 
 scalar_t__ sscanf (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct buffer query_parse_integer(struct buffer buff,
      struct rmsgpack_dom_value *value, const char **error)
{
   bool test   = false;

   value->type = RDT_INT;

   test        = (sscanf(buff.data + buff.offset,
                         STRING_REP_INT64,
                         (int64_t*)&value->val.int_) == 0);

   if (test)
      query_raise_expected_number(buff.offset, error);
   else
   {
      while (isdigit((int)buff.data[buff.offset]))
         buff.offset++;
   }

   return buff;
}