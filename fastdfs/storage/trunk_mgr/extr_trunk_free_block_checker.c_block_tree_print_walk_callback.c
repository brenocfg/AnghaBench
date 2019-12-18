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
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int count; TYPE_4__** blocks; } ;
struct TYPE_7__ {int id; int offset; int size; } ;
struct TYPE_6__ {int store_path_index; int sub_path_high; int sub_path_low; } ;
struct TYPE_9__ {TYPE_2__ file; TYPE_1__ path; } ;
struct TYPE_8__ {TYPE_5__ block_array; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_3__ FDFSTrunksById ;
typedef  TYPE_4__ FDFSTrunkFullInfo ;
typedef  TYPE_5__ FDFSBlockArray ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int,int,int,int,int) ; 

__attribute__((used)) static int block_tree_print_walk_callback(void *data, void *args)
{
	FILE *fp;
	FDFSBlockArray *pArray;
	FDFSTrunkFullInfo **pp;
	FDFSTrunkFullInfo **ppEnd;

	fp = (FILE *)args;
	pArray = &(((FDFSTrunksById *)data)->block_array);

	/*
	{
	FDFSTrunkFileIdentifier *pFileIdentifier;
	pFileIdentifier = &(((FDFSTrunksById *)data)->trunk_file_id);

	fprintf(fp, "%d %d %d %d %d", \
			pFileIdentifier->path.store_path_index, \
			pFileIdentifier->path.sub_path_high, \
			pFileIdentifier->path.sub_path_low, \
			pFileIdentifier->id, pArray->count);
	if (pArray->count > 0)
	{
		fprintf(fp, " %d", pArray->blocks[0]->file.offset);
		if (pArray->count > 1)
		{
			fprintf(fp, " %d", pArray->blocks[pArray->count-1]-> \
				file.offset + pArray->blocks[pArray->count-1]->\
				file.size);
		}
	}
	fprintf(fp, "\n");
	return 0;
	}
	*/

	/*
	{
	FDFSTrunkFullInfo **ppPrevious;
	if (pArray->count <= 1)
	{
		return 0;
	}
	ppPrevious = pArray->blocks;
	ppEnd = pArray->blocks + pArray->count;
	for (pp=pArray->blocks + 1; pp<ppEnd; pp++)
	{
		if ((*ppPrevious)->file.offset >= (*pp)->file.offset)
		{
			fprintf(fp, "%d %d %d %d %d %d\n", \
				(*ppPrevious)->path.store_path_index, \
				(*ppPrevious)->path.sub_path_high, (*ppPrevious)->path.sub_path_low, \
				(*ppPrevious)->file.id, (*ppPrevious)->file.offset, (*ppPrevious)->file.size);

			fprintf(fp, "%d %d %d %d %d %d\n", \
				(*pp)->path.store_path_index, \
				(*pp)->path.sub_path_high, (*pp)->path.sub_path_low, \
				(*pp)->file.id, (*pp)->file.offset, (*pp)->file.size);
		}
		ppPrevious = pp;
	}
	return 0;
	}
	*/

	ppEnd = pArray->blocks + pArray->count;
	for (pp=pArray->blocks; pp<ppEnd; pp++)
	{
		fprintf(fp, "%d %d %d %d %d %d\n", \
			(*pp)->path.store_path_index, \
			(*pp)->path.sub_path_high, (*pp)->path.sub_path_low, \
			(*pp)->file.id, (*pp)->file.offset, (*pp)->file.size);
	}

	return 0;
}