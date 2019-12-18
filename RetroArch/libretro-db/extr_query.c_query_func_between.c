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
struct TYPE_5__ {int bool_; int /*<<< orphan*/  int_; } ;
struct rmsgpack_dom_value {int type; TYPE_1__ val; } ;
struct TYPE_6__ {unsigned int uint_; int /*<<< orphan*/  int_; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ val; } ;
struct TYPE_8__ {TYPE_3__ value; } ;
struct argument {scalar_t__ type; TYPE_4__ a; } ;

/* Variables and functions */
 scalar_t__ AT_VALUE ; 
 int RDT_BOOL ; 
#define  RDT_INT 129 
#define  RDT_UINT 128 

__attribute__((used)) static struct rmsgpack_dom_value query_func_between(
      struct rmsgpack_dom_value input,
      unsigned argc, const struct argument * argv)
{
   struct rmsgpack_dom_value res;
   unsigned i                     = 0;

   res.type      = RDT_BOOL;
   res.val.bool_ = 0;

   (void)i;

   if (argc != 2)
      return res;
   if (argv[0].type != AT_VALUE || argv[1].type != AT_VALUE)
      return res;
   if (argv[0].a.value.type != RDT_INT || argv[1].a.value.type != RDT_INT)
      return res;

   switch (input.type)
   {
      case RDT_INT:
         res.val.bool_ = (
               (input.val.int_ >= argv[0].a.value.val.int_)
               && (input.val.int_ <= argv[1].a.value.val.int_));
         break;
      case RDT_UINT:
         res.val.bool_ = (
               ((unsigned)input.val.int_ >= argv[0].a.value.val.uint_)
               && (input.val.int_ <= argv[1].a.value.val.int_));
         break;
      default:
         return res;
   }

   return res;
}