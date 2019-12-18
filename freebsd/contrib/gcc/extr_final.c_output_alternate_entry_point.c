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
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_3__ {int /*<<< orphan*/  (* globalize_label ) (int /*<<< orphan*/ *,char const*) ;} ;
struct TYPE_4__ {TYPE_1__ asm_out; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_OUTPUT_LABEL (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ASM_OUTPUT_TYPE_DIRECTIVE (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  ASM_WEAKEN_LABEL (int /*<<< orphan*/ *,char const*) ; 
#define  LABEL_GLOBAL_ENTRY 131 
 int LABEL_KIND (int /*<<< orphan*/ ) ; 
 char* LABEL_NAME (int /*<<< orphan*/ ) ; 
#define  LABEL_NORMAL 130 
#define  LABEL_STATIC_ENTRY 129 
#define  LABEL_WEAK_ENTRY 128 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char const*) ; 
 TYPE_2__ targetm ; 

__attribute__((used)) static void
output_alternate_entry_point (FILE *file, rtx insn)
{
  const char *name = LABEL_NAME (insn);

  switch (LABEL_KIND (insn))
    {
    case LABEL_WEAK_ENTRY:
#ifdef ASM_WEAKEN_LABEL
      ASM_WEAKEN_LABEL (file, name);
#endif
    case LABEL_GLOBAL_ENTRY:
      targetm.asm_out.globalize_label (file, name);
    case LABEL_STATIC_ENTRY:
#ifdef ASM_OUTPUT_TYPE_DIRECTIVE
      ASM_OUTPUT_TYPE_DIRECTIVE (file, name, "function");
#endif
      ASM_OUTPUT_LABEL (file, name);
      break;

    case LABEL_NORMAL:
    default:
      gcc_unreachable ();
    }
}