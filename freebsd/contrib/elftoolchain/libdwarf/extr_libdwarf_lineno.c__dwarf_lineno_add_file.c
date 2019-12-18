#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct _Dwarf_LineFile {int dummy; } ;
struct TYPE_8__ {char* lf_fname; int lf_dirndx; void* lf_size; void* lf_mtime; int /*<<< orphan*/ * lf_fullpath; } ;
struct TYPE_7__ {int li_inclen; char** li_incdirs; int /*<<< orphan*/  li_lflen; int /*<<< orphan*/  li_lflist; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__* Dwarf_LineInfo ;
typedef  TYPE_2__* Dwarf_LineFile ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_DIR_INDEX_BAD ; 
 int DW_DLE_MEMORY ; 
 int DW_DLE_NONE ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* _dwarf_decode_uleb128 (int /*<<< orphan*/ **) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  lf_next ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/ * open_memstream (int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
_dwarf_lineno_add_file(Dwarf_LineInfo li, uint8_t **p, const char *compdir,
    Dwarf_Error *error, Dwarf_Debug dbg)
{
	Dwarf_LineFile lf;
	FILE *filepath;
	const char *incdir;
	uint8_t *src;
	size_t slen;

	src = *p;

	if ((lf = malloc(sizeof(struct _Dwarf_LineFile))) == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLE_MEMORY);
	}

	lf->lf_fullpath = NULL;
	lf->lf_fname = (char *) src;
	src += strlen(lf->lf_fname) + 1;
	lf->lf_dirndx = _dwarf_decode_uleb128(&src);
	if (lf->lf_dirndx > li->li_inclen) {
		free(lf);
		DWARF_SET_ERROR(dbg, error, DW_DLE_DIR_INDEX_BAD);
		return (DW_DLE_DIR_INDEX_BAD);
	}

	/* Make a full pathname if needed. */
	if (*lf->lf_fname != '/') {
		filepath = open_memstream(&lf->lf_fullpath, &slen);
		if (filepath == NULL) {
			free(lf);
			DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
			return (DW_DLE_MEMORY);
		}

		if (lf->lf_dirndx > 0)
			incdir = li->li_incdirs[lf->lf_dirndx - 1];
		else
			incdir = NULL;

		/*
		 * Prepend the compilation directory if the directory table
		 * entry is relative.
		 */
		if (incdir == NULL || *incdir != '/')
			fprintf(filepath, "%s/", compdir);
		if (incdir != NULL)
			fprintf(filepath, "%s/", incdir);
		fprintf(filepath, "%s", lf->lf_fname);
		if (fclose(filepath) != 0) {
			free(lf);
			DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
			return (DW_DLE_MEMORY);
		}
	}

	lf->lf_mtime = _dwarf_decode_uleb128(&src);
	lf->lf_size = _dwarf_decode_uleb128(&src);
	STAILQ_INSERT_TAIL(&li->li_lflist, lf, lf_next);
	li->li_lflen++;

	*p = src;

	return (DW_DLE_NONE);
}