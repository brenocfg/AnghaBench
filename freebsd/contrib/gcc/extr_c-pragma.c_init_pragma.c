#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  omp_pragmas ;

/* Variables and functions */
 unsigned int PRAGMA_GCC_PCH_PREPROCESS ; 
#define  PRAGMA_OMP_ATOMIC 139 
#define  PRAGMA_OMP_BARRIER 138 
#define  PRAGMA_OMP_CRITICAL 137 
#define  PRAGMA_OMP_FLUSH 136 
#define  PRAGMA_OMP_FOR 135 
#define  PRAGMA_OMP_MASTER 134 
#define  PRAGMA_OMP_ORDERED 133 
#define  PRAGMA_OMP_PARALLEL 132 
#define  PRAGMA_OMP_SECTION 131 
#define  PRAGMA_OMP_SECTIONS 130 
#define  PRAGMA_OMP_SINGLE 129 
#define  PRAGMA_OMP_THREADPRIVATE 128 
 int /*<<< orphan*/  REGISTER_TARGET_PRAGMAS () ; 
 int /*<<< orphan*/  c_register_pragma (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_register_pragma_with_expansion (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpp_register_deferred_pragma (int /*<<< orphan*/ ,char*,char*,unsigned int,int,int) ; 
 scalar_t__ flag_openmp ; 
 int /*<<< orphan*/  flag_preprocess_only ; 
 int /*<<< orphan*/  handle_pragma_diagnostic ; 
 int /*<<< orphan*/  handle_pragma_extern_prefix ; 
 int /*<<< orphan*/  handle_pragma_pack ; 
 int /*<<< orphan*/  handle_pragma_redefine_extname ; 
 int /*<<< orphan*/  handle_pragma_visibility ; 
 int /*<<< orphan*/  handle_pragma_weak ; 
 int /*<<< orphan*/  parse_in ; 

void
init_pragma (void)
{
  if (flag_openmp && !flag_preprocess_only)
    {
      struct omp_pragma_def { const char *name; unsigned int id; };
      static const struct omp_pragma_def omp_pragmas[] = {
	{ "atomic", PRAGMA_OMP_ATOMIC },
	{ "barrier", PRAGMA_OMP_BARRIER },
	{ "critical", PRAGMA_OMP_CRITICAL },
	{ "flush", PRAGMA_OMP_FLUSH },
	{ "for", PRAGMA_OMP_FOR },
	{ "master", PRAGMA_OMP_MASTER },
	{ "ordered", PRAGMA_OMP_ORDERED },
	{ "parallel", PRAGMA_OMP_PARALLEL },
	{ "section", PRAGMA_OMP_SECTION },
	{ "sections", PRAGMA_OMP_SECTIONS },
	{ "single", PRAGMA_OMP_SINGLE },
	{ "threadprivate", PRAGMA_OMP_THREADPRIVATE }
      };

      const int n_omp_pragmas = sizeof (omp_pragmas) / sizeof (*omp_pragmas);
      int i;

      for (i = 0; i < n_omp_pragmas; ++i)
	cpp_register_deferred_pragma (parse_in, "omp", omp_pragmas[i].name,
				      omp_pragmas[i].id, true, true);
    }

  cpp_register_deferred_pragma (parse_in, "GCC", "pch_preprocess",
				PRAGMA_GCC_PCH_PREPROCESS, false, false);

#ifdef HANDLE_PRAGMA_PACK
#ifdef HANDLE_PRAGMA_PACK_WITH_EXPANSION
  c_register_pragma_with_expansion (0, "pack", handle_pragma_pack);
#else
  c_register_pragma (0, "pack", handle_pragma_pack);
#endif
#endif
#ifdef HANDLE_PRAGMA_WEAK
  c_register_pragma (0, "weak", handle_pragma_weak);
#endif
#ifdef HANDLE_PRAGMA_VISIBILITY
  c_register_pragma ("GCC", "visibility", handle_pragma_visibility);
#endif

  c_register_pragma ("GCC", "diagnostic", handle_pragma_diagnostic);

  c_register_pragma_with_expansion (0, "redefine_extname", handle_pragma_redefine_extname);
  c_register_pragma (0, "extern_prefix", handle_pragma_extern_prefix);

#ifdef REGISTER_TARGET_PRAGMAS
  REGISTER_TARGET_PRAGMAS ();
#endif
}