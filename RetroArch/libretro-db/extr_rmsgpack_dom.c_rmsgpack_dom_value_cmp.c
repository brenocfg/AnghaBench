#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {unsigned int len; struct rmsgpack_dom_value* items; } ;
struct TYPE_10__ {unsigned int len; TYPE_3__* items; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buff; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buff; } ;
struct TYPE_12__ {TYPE_5__ array; TYPE_4__ map; TYPE_2__ binary; TYPE_1__ string; int /*<<< orphan*/  uint_; int /*<<< orphan*/  int_; int /*<<< orphan*/  bool_; } ;
struct rmsgpack_dom_value {int type; TYPE_6__ val; } ;
struct TYPE_9__ {struct rmsgpack_dom_value value; struct rmsgpack_dom_value key; } ;

/* Variables and functions */
#define  RDT_ARRAY 135 
#define  RDT_BINARY 134 
#define  RDT_BOOL 133 
#define  RDT_INT 132 
#define  RDT_MAP 131 
#define  RDT_NULL 130 
#define  RDT_STRING 129 
#define  RDT_UINT 128 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rmsgpack_dom_value_cmp(
      const struct rmsgpack_dom_value *a,
      const struct rmsgpack_dom_value *b
)
{
   int rv;
   unsigned i;

   if (a == b)
      return 1;

   if (a->type != b->type)
      return 1;

   switch (a->type)
   {
      case RDT_NULL:
         return 0;
      case RDT_BOOL:
         return a->val.bool_ == b->val.bool_ ? 0 : 1;
      case RDT_INT:
         return a->val.int_ == b->val.int_ ? 0 : 1;
      case RDT_UINT:
         return a->val.uint_ == b->val.uint_ ? 0 : 1;
      case RDT_STRING:
         if (a->val.string.len != b->val.string.len)
            return 1;
         return strncmp(a->val.string.buff, b->val.string.buff, a->val.string.len);
      case RDT_BINARY:
         if (a->val.binary.len != b->val.binary.len)
            return 1;
         return memcmp(a->val.binary.buff, b->val.binary.buff, a->val.binary.len);
      case RDT_MAP:
         if (a->val.map.len != b->val.map.len)
            return 1;
         for (i = 0; i < a->val.map.len; i++)
         {
            if ((rv = rmsgpack_dom_value_cmp(&a->val.map.items[i].key,
                        &b->val.map.items[i].key)) != 0)
               return rv;
            if ((rv = rmsgpack_dom_value_cmp(&a->val.map.items[i].value,
                        &b->val.map.items[i].value)) != 0)
               return rv;
         }
         break;
      case RDT_ARRAY:
         if (a->val.array.len != b->val.array.len)
            return 1;
         for (i = 0; i < a->val.array.len; i++)
         {
            if ((rv = rmsgpack_dom_value_cmp(&a->val.array.items[i],
                        &b->val.array.items[i])) != 0)
               return rv;
         }
         break;
   }

   return 1;
}