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
struct TYPE_2__ {scalar_t__ s_ndata; scalar_t__ s_nfunc; scalar_t__ s_nargs; scalar_t__ s_argmax; scalar_t__ s_ntypes; scalar_t__* s_types; scalar_t__ s_nsmem; scalar_t__ s_smmax; scalar_t__ s_nsbytes; scalar_t__ s_sbmax; scalar_t__ s_numem; scalar_t__ s_ummax; scalar_t__ s_nubytes; scalar_t__ s_ubmax; scalar_t__ s_nemem; scalar_t__ s_emmax; scalar_t__ s_nstr; scalar_t__ s_strlen; scalar_t__ s_strmax; } ;

/* Variables and functions */
 size_t CTF_K_ARRAY ; 
 size_t CTF_K_CONST ; 
 size_t CTF_K_ENUM ; 
 size_t CTF_K_FLOAT ; 
 size_t CTF_K_FORWARD ; 
 size_t CTF_K_FUNCTION ; 
 size_t CTF_K_INTEGER ; 
 size_t CTF_K_POINTER ; 
 size_t CTF_K_RESTRICT ; 
 size_t CTF_K_STRUCT ; 
 size_t CTF_K_TYPEDEF ; 
 size_t CTF_K_UNION ; 
 size_t CTF_K_UNKNOWN ; 
 size_t CTF_K_VOLATILE ; 
 int E_SUCCESS ; 
 int /*<<< orphan*/  fp_stat (char*,float) ; 
 int /*<<< orphan*/  long_stat (char*,scalar_t__) ; 
 int /*<<< orphan*/  print_line (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_1__ stats ; 

__attribute__((used)) static int
print_stats(void)
{
	print_line("- CTF Statistics ");

	long_stat("total number of data objects", stats.s_ndata);
	(void) printf("\n");

	long_stat("total number of functions", stats.s_nfunc);
	long_stat("total number of function arguments", stats.s_nargs);
	long_stat("maximum argument list length", stats.s_argmax);

	if (stats.s_nfunc != 0) {
		fp_stat("average argument list length",
		    (float)stats.s_nargs / (float)stats.s_nfunc);
	}

	(void) printf("\n");

	long_stat("total number of types", stats.s_ntypes);
	long_stat("total number of integers", stats.s_types[CTF_K_INTEGER]);
	long_stat("total number of floats", stats.s_types[CTF_K_FLOAT]);
	long_stat("total number of pointers", stats.s_types[CTF_K_POINTER]);
	long_stat("total number of arrays", stats.s_types[CTF_K_ARRAY]);
	long_stat("total number of func types", stats.s_types[CTF_K_FUNCTION]);
	long_stat("total number of structs", stats.s_types[CTF_K_STRUCT]);
	long_stat("total number of unions", stats.s_types[CTF_K_UNION]);
	long_stat("total number of enums", stats.s_types[CTF_K_ENUM]);
	long_stat("total number of forward tags", stats.s_types[CTF_K_FORWARD]);
	long_stat("total number of typedefs", stats.s_types[CTF_K_TYPEDEF]);
	long_stat("total number of volatile types",
	    stats.s_types[CTF_K_VOLATILE]);
	long_stat("total number of const types", stats.s_types[CTF_K_CONST]);
	long_stat("total number of restrict types",
	    stats.s_types[CTF_K_RESTRICT]);
	long_stat("total number of unknowns (holes)",
	    stats.s_types[CTF_K_UNKNOWN]);

	(void) printf("\n");

	long_stat("total number of struct members", stats.s_nsmem);
	long_stat("maximum number of struct members", stats.s_smmax);
	long_stat("total size of all structs", stats.s_nsbytes);
	long_stat("maximum size of a struct", stats.s_sbmax);

	if (stats.s_types[CTF_K_STRUCT] != 0) {
		fp_stat("average number of struct members",
		    (float)stats.s_nsmem / (float)stats.s_types[CTF_K_STRUCT]);
		fp_stat("average size of a struct", (float)stats.s_nsbytes /
		    (float)stats.s_types[CTF_K_STRUCT]);
	}

	(void) printf("\n");

	long_stat("total number of union members", stats.s_numem);
	long_stat("maximum number of union members", stats.s_ummax);
	long_stat("total size of all unions", stats.s_nubytes);
	long_stat("maximum size of a union", stats.s_ubmax);

	if (stats.s_types[CTF_K_UNION] != 0) {
		fp_stat("average number of union members",
		    (float)stats.s_numem / (float)stats.s_types[CTF_K_UNION]);
		fp_stat("average size of a union", (float)stats.s_nubytes /
		    (float)stats.s_types[CTF_K_UNION]);
	}

	(void) printf("\n");

	long_stat("total number of enum members", stats.s_nemem);
	long_stat("maximum number of enum members", stats.s_emmax);

	if (stats.s_types[CTF_K_ENUM] != 0) {
		fp_stat("average number of enum members",
		    (float)stats.s_nemem / (float)stats.s_types[CTF_K_ENUM]);
	}

	(void) printf("\n");

	long_stat("total number of unique strings", stats.s_nstr);
	long_stat("bytes of string data", stats.s_strlen);
	long_stat("maximum string length", stats.s_strmax);

	if (stats.s_nstr != 0) {
		fp_stat("average string length",
		    (float)stats.s_strlen / (float)stats.s_nstr);
	}

	(void) printf("\n");
	return (E_SUCCESS);
}