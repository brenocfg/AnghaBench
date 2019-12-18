#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct invocation {unsigned int argc; struct argument* argv; int /*<<< orphan*/  func; } ;
struct buffer {size_t offset; scalar_t__* data; } ;
struct TYPE_5__ {char* buff; scalar_t__ len; } ;
struct TYPE_6__ {TYPE_1__ string; } ;
struct TYPE_8__ {TYPE_2__ val; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {TYPE_4__ value; } ;
struct argument {int /*<<< orphan*/  type; TYPE_3__ a; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_VALUE ; 
 int QUERY_MAX_ARGS ; 
 int /*<<< orphan*/  RDT_STRING ; 
 scalar_t__ calloc (size_t,int) ; 
 scalar_t__ isalpha (int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct argument*,struct argument*,int) ; 
 int /*<<< orphan*/  query_argument_free (struct argument*) ; 
 struct buffer query_chomp (struct buffer) ; 
 struct buffer query_expect_char (struct buffer,char,char const**) ; 
 int /*<<< orphan*/  query_func_all_map ; 
 struct buffer query_get_ident (struct buffer,char const**,size_t*,char const**) ; 
 struct buffer query_parse_argument (struct buffer,struct argument*,char const**) ; 
 struct buffer query_parse_string (struct buffer,TYPE_4__*,char const**) ; 
 int /*<<< orphan*/  query_peek (struct buffer,char*) ; 
 int /*<<< orphan*/  query_raise_enomem (char const**) ; 
 int /*<<< orphan*/  query_raise_too_many_arguments (char const**) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static struct buffer query_parse_table(struct buffer buff,
      struct invocation *invocation, const char **error)
{
   unsigned i;
   size_t ident_len;
   struct argument args[QUERY_MAX_ARGS];
   const char *ident_name = NULL;
   unsigned argi = 0;

   buff = query_chomp(buff);
   buff = query_expect_char(buff, '{', error);

   if (*error)
      goto clean;

   buff = query_chomp(buff);

   while (!query_peek(buff, "}"))
   {
      if (argi >= QUERY_MAX_ARGS)
      {
         query_raise_too_many_arguments(error);
         goto clean;
      }

      if (isalpha((int)buff.data[buff.offset]))
      {
         buff = query_get_ident(buff, &ident_name, &ident_len, error);

         if (!*error)
         {
            args[argi].a.value.type            = RDT_STRING;
            args[argi].a.value.val.string.len  = (uint32_t)ident_len;
            args[argi].a.value.val.string.buff = (char*)calloc(
                  ident_len + 1,
                  sizeof(char)
                  );

            if (!args[argi].a.value.val.string.buff)
               goto clean;

            strncpy(
                  args[argi].a.value.val.string.buff,
                  ident_name,
                  ident_len
                  );
         }
      }
      else
         buff = query_parse_string(buff, &args[argi].a.value, error);

      if (*error)
         goto clean;

      args[argi].type = AT_VALUE;
      buff            = query_chomp(buff);
      argi++;
      buff = query_expect_char(buff, ':', error);

      if (*error)
         goto clean;

      buff = query_chomp(buff);

      if (argi >= QUERY_MAX_ARGS)
      {
         query_raise_too_many_arguments(error);
         goto clean;
      }

      buff = query_parse_argument(buff, &args[argi], error);

      if (*error)
         goto clean;
      argi++;
      buff = query_chomp(buff);
      buff = query_expect_char(buff, ',', error);

      if (*error)
      {
         *error = NULL;
         break;
      }
      buff = query_chomp(buff);
   }

   buff = query_expect_char(buff, '}', error);

   if (*error)
      goto clean;

   invocation->func = query_func_all_map;
   invocation->argc = argi;
   invocation->argv = (struct argument*)
      malloc(sizeof(struct argument) * argi);

   if (!invocation->argv)
   {
      query_raise_enomem(error);
      goto clean;
   }
   memcpy(invocation->argv, args,
         sizeof(struct argument) * argi);

   goto success;
clean:
   for (i = 0; i < argi; i++)
      query_argument_free(&args[i]);
success:
   return buff;
}