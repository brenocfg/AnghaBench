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
struct TYPE_7__ {scalar_t__ len; char* buff; } ;
struct TYPE_6__ {unsigned int len; TYPE_1__* items; } ;
struct TYPE_8__ {TYPE_3__ string; TYPE_2__ map; } ;
struct rmsgpack_dom_value {scalar_t__ type; TYPE_4__ val; } ;
struct TYPE_5__ {struct rmsgpack_dom_value value; struct rmsgpack_dom_value key; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RDT_MAP ; 
 scalar_t__ RDT_STRING ; 

__attribute__((used)) static int libretrodb_validate_document(const struct rmsgpack_dom_value *doc)
{
   unsigned i;
   struct rmsgpack_dom_value key, value;
   int rv = 0;

   if (doc->type != RDT_MAP)
      return -EINVAL;

   for (i = 0; i < doc->val.map.len; i++)
   {
      key = doc->val.map.items[i].key;
      value = doc->val.map.items[i].value;

      if (key.type != RDT_STRING)
         return -EINVAL;

      if (key.val.string.len <= 0)
         return -EINVAL;

      if (key.val.string.buff[0] == '$')
         return -EINVAL;

      if (value.type != RDT_MAP)
         continue;

      if ((rv == libretrodb_validate_document(&value)) != 0)
         return rv;
   }

   return rv;
}