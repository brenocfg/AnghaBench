#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  Tuplestorestate ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  BoolGetDatum (int) ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cstring_to_text_with_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tuplestore_begin_heap (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_donestoring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplestore_puttuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  work_mem ; 

__attribute__((used)) static Tuplestorestate *
CreateTupleStore(TupleDesc tupleDescriptor,
				 StringInfo *nodeNameArray, int *nodePortArray, bool *statusArray,
				 StringInfo *resultArray, int commandCount)
{
	Tuplestorestate *tupleStore = tuplestore_begin_heap(true, false, work_mem);
	int commandIndex = 0;
	bool nulls[4] = { false, false, false, false };

	for (commandIndex = 0; commandIndex < commandCount; commandIndex++)
	{
		Datum values[4];
		HeapTuple tuple = NULL;
		StringInfo nodeNameString = nodeNameArray[commandIndex];
		StringInfo resultString = resultArray[commandIndex];
		text *nodeNameText = cstring_to_text_with_len(nodeNameString->data,
													  nodeNameString->len);
		text *resultText = cstring_to_text_with_len(resultString->data,
													resultString->len);

		values[0] = PointerGetDatum(nodeNameText);
		values[1] = Int32GetDatum(nodePortArray[commandIndex]);
		values[2] = BoolGetDatum(statusArray[commandIndex]);
		values[3] = PointerGetDatum(resultText);

		tuple = heap_form_tuple(tupleDescriptor, values, nulls);
		tuplestore_puttuple(tupleStore, tuple);

		heap_freetuple(tuple);
		pfree(nodeNameText);
		pfree(resultText);
	}

	tuplestore_donestoring(tupleStore);

	return tupleStore;
}