#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* decl_t ;
struct TYPE_10__ {void* regexp; } ;
struct TYPE_9__ {void* regexp; } ;
struct TYPE_8__ {int decls_num; TYPE_1__** decls; } ;
struct TYPE_7__ {scalar_t__ mode; } ;

/* Variables and functions */
 TYPE_5__* DECL_INSN_RESERV (TYPE_1__*) ; 
 TYPE_3__* DECL_RESERV (TYPE_1__*) ; 
 TYPE_2__* description ; 
 scalar_t__ dm_insn_reserv ; 
 scalar_t__ dm_reserv ; 
 void* process_regexp (void*) ; 

__attribute__((used)) static void
process_regexp_decls (void)
{
  decl_t decl;
  int i;

  for (i = 0; i < description->decls_num; i++)
    {
      decl = description->decls [i];
      if (decl->mode == dm_reserv)
	DECL_RESERV (decl)->regexp
	  = process_regexp (DECL_RESERV (decl)->regexp);
      else if (decl->mode == dm_insn_reserv)
	DECL_INSN_RESERV (decl)->regexp
	  = process_regexp (DECL_INSN_RESERV (decl)->regexp);
    }
}