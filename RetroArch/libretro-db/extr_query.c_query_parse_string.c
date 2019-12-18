#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int len; char* buff; } ;
struct TYPE_4__ {TYPE_1__ string; } ;
struct rmsgpack_dom_value {TYPE_2__ val; int /*<<< orphan*/  type; } ;
struct buffer {int offset; char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDT_BINARY ; 
 int /*<<< orphan*/  RDT_STRING ; 
 scalar_t__ calloc (size_t,int) ; 
 int /*<<< orphan*/  memcpy (int*,char const*,unsigned int) ; 
 struct buffer query_get_char (struct buffer,char*,char const**) ; 
 int /*<<< orphan*/  query_raise_enomem (char const**) ; 
 int /*<<< orphan*/  query_raise_expected_string (int,char const**) ; 

__attribute__((used)) static struct buffer query_parse_string(struct buffer buff,
      struct rmsgpack_dom_value *value, const char **error)
{
   const char * str_start = NULL;
   char terminator        = '\0';
   char c                 = '\0';
   int  is_binstr         = 0;

   (void)c;

   buff = query_get_char(buff, &terminator, error);

   if (*error)
      return buff;

   if (terminator == 'b')
   {
      is_binstr = 1;
      buff = query_get_char(buff, &terminator, error);
   }

   if (terminator != '"' && terminator != '\'')
   {
      buff.offset--;
      query_raise_expected_string(buff.offset, error);
   }

   str_start = buff.data + buff.offset;
   buff      = query_get_char(buff, &c, error);

   while (!*error)
   {
      if (c == terminator)
         break;
      buff = query_get_char(buff, &c, error);
   }

   if (!*error)
   {
      size_t count;
      value->type            = is_binstr ? RDT_BINARY : RDT_STRING;
      value->val.string.len  = (uint32_t)((buff.data + buff.offset) - str_start - 1);

      count                  = is_binstr ? (value->val.string.len + 1) / 2
         : (value->val.string.len + 1);
      value->val.string.buff = (char*)calloc(count, sizeof(char));

      if (!value->val.string.buff)
         query_raise_enomem(error);
      else if (is_binstr)
      {
         unsigned i;
         const char *tok = str_start;
         unsigned      j = 0;

         for (i = 0; i < value->val.string.len; i += 2)
         {
            uint8_t hi, lo;
            char hic = tok[i];
            char loc = tok[i + 1];

            if (hic <= '9')
               hi = hic - '0';
            else
               hi = (hic - 'A') + 10;

            if (loc <= '9')
               lo = loc - '0';
            else
               lo = (loc - 'A') + 10;

            value->val.string.buff[j++] = hi * 16 + lo;
         }

         value->val.string.len = j;
      }
      else
         memcpy(value->val.string.buff, str_start, value->val.string.len);
   }
   return buff;
}