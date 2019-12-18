#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {char* value; struct TYPE_18__* next; } ;
typedef  TYPE_3__ dat_converter_match_key_t ;
struct TYPE_16__ {int /*<<< orphan*/ * list; } ;
struct TYPE_19__ {char* key; TYPE_1__ value; void* type; } ;
typedef  TYPE_4__ dat_converter_map_t ;
struct TYPE_20__ {TYPE_6__* values; } ;
typedef  TYPE_5__ dat_converter_list_t ;
struct TYPE_17__ {char* label; int line_no; char* fname; int column; } ;
struct TYPE_21__ {TYPE_2__ token; } ;
typedef  TYPE_6__ dat_converter_list_item_t ;

/* Variables and functions */
 void* DAT_CONVERTER_LIST_MAP ; 
 int /*<<< orphan*/  DAT_CONVERTER_MAP_LIST ; 
 int /*<<< orphan*/  dat_converter_exit (int) ; 
 char* dat_converter_get_match (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  dat_converter_list_append (TYPE_5__*,TYPE_4__*) ; 
 TYPE_5__* dat_converter_list_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dat_converter_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dat_parser_table (TYPE_6__**) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ string_is_equal (char*,char*) ; 

__attribute__((used)) static dat_converter_list_t* dat_converter_parser(
      dat_converter_list_t* target,
      dat_converter_list_t* lexer_list,
      dat_converter_match_key_t* match_key)
{
   dat_converter_map_t map;
   dat_converter_list_item_t* current = lexer_list->values;
   bool skip                          = true;
   bool warning_displayed             = false;

   map.key                            = NULL;
   map.type                           = DAT_CONVERTER_LIST_MAP;

   if (!target)
   {
      dat_converter_map_t map;
      target = dat_converter_list_create(DAT_CONVERTER_MAP_LIST);
      map.key = NULL;
      map.type = DAT_CONVERTER_LIST_MAP;
      map.value.list = NULL;
      dat_converter_list_append(target, &map);
   }

   while (current->token.label)
   {
      if (!map.key)
      {
         if (string_is_equal(current->token.label, "game"))
            skip = false;
         map.key = current->token.label;
         current++;
      }
      else
      {
         if (string_is_equal(current->token.label, "("))
         {
            current++;
            map.value.list = dat_parser_table(&current);
            if (!skip)
            {
               if (match_key)
               {
                  map.key = dat_converter_get_match(map.value.list, match_key);
                  // If the key is not found, report, and mark it to be skipped.
                  if (!map.key)
                  {
                     if (warning_displayed == false)
                     {
                        printf("    - Missing match key '");
                        while (match_key->next)
                        {
                           printf("%s.", match_key->value);
                           match_key = match_key->next;
                        }
                        printf("%s' on line %d\n", match_key->value, current->token.line_no);
                        warning_displayed = true;
                     }
                     skip = true;
                  }
               }
               else
                  map.key = NULL;

               // If we are still not to skip the entry, append it to the list.
               if (!skip) {
                  dat_converter_list_append(target, &map);
                  skip = true;
               }
            }
            else
               dat_converter_list_free(map.value.list);

            map.key = NULL;
         }
         else
         {
            printf("%s:%d:%d: fatal error: Expected '(' found '%s'\n",
                   current->token.fname,
                   current->token.line_no,
                   current->token.column,
                   current->token.label);
            dat_converter_exit(1);
         }
      }
   }
   return target;
}