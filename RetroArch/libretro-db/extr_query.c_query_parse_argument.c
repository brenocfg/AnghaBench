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
struct buffer {size_t offset; scalar_t__* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; int /*<<< orphan*/  invocation; } ;
struct argument {TYPE_1__ a; void* type; } ;

/* Variables and functions */
 void* AT_FUNCTION ; 
 void* AT_VALUE ; 
 scalar_t__ isalpha (int) ; 
 struct buffer query_chomp (struct buffer) ; 
 struct buffer query_parse_method_call (struct buffer,int /*<<< orphan*/ *,char const**) ; 
 struct buffer query_parse_table (struct buffer,int /*<<< orphan*/ *,char const**) ; 
 struct buffer query_parse_value (struct buffer,int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ query_peek (struct buffer,char*) ; 

__attribute__((used)) static struct buffer query_parse_argument(struct buffer buff,
      struct argument *arg, const char **error)
{
   buff = query_chomp(buff);

   if (
         isalpha((int)buff.data[buff.offset])
         && !(
               query_peek(buff, "nil")
            || query_peek(buff, "true")
            || query_peek(buff, "false")
            || query_peek(buff, "b\"")
            || query_peek(buff,  "b'") /* bin string prefix*/
            )
      )
   {
      arg->type = AT_FUNCTION;
      buff      = query_parse_method_call(buff,
            &arg->a.invocation, error);
   }
   else if (query_peek(buff, "{"))
   {
      arg->type = AT_FUNCTION;
      buff      = query_parse_table(buff, &arg->a.invocation, error);
   }
   else
   {
      arg->type = AT_VALUE;
      buff      = query_parse_value(buff, &arg->a.value, error);
   }
   return buff;
}