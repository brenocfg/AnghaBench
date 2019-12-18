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
typedef  int /*<<< orphan*/  text ;
typedef  int int32 ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int ArrayObjectCount (int /*<<< orphan*/ *) ; 
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DatumGetTextP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DeconstructArrayObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * PG_GETARG_ARRAYTYPE_P (int) ; 
 int PG_GETARG_BOOL (int) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  makeStringInfo () ; 
 void* palloc0 (int) ; 
 char* text_to_cstring (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ParseCommandParameters(FunctionCallInfo fcinfo, StringInfo **nodeNameArray,
					   int **nodePortsArray, StringInfo **commandStringArray,
					   bool *parallel)
{
	ArrayType *nodeNameArrayObject = PG_GETARG_ARRAYTYPE_P(0);
	ArrayType *nodePortArrayObject = PG_GETARG_ARRAYTYPE_P(1);
	ArrayType *commandStringArrayObject = PG_GETARG_ARRAYTYPE_P(2);
	bool parallelExecution = PG_GETARG_BOOL(3);
	int nodeNameCount = ArrayObjectCount(nodeNameArrayObject);
	int nodePortCount = ArrayObjectCount(nodePortArrayObject);
	int commandStringCount = ArrayObjectCount(commandStringArrayObject);
	Datum *nodeNameDatumArray = DeconstructArrayObject(nodeNameArrayObject);
	Datum *nodePortDatumArray = DeconstructArrayObject(nodePortArrayObject);
	Datum *commandStringDatumArray = DeconstructArrayObject(commandStringArrayObject);
	int index = 0;
	StringInfo *nodeNames = NULL;
	int *nodePorts = NULL;
	StringInfo *commandStrings = NULL;

	if (nodeNameCount != nodePortCount || nodeNameCount != commandStringCount)
	{
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("expected same number of node name, port, and query string")));
	}

	nodeNames = palloc0(nodeNameCount * sizeof(StringInfo));
	nodePorts = palloc0(nodeNameCount * sizeof(int));
	commandStrings = palloc0(nodeNameCount * sizeof(StringInfo));

	for (index = 0; index < nodeNameCount; index++)
	{
		text *nodeNameText = DatumGetTextP(nodeNameDatumArray[index]);
		char *nodeName = text_to_cstring(nodeNameText);
		int32 nodePort = DatumGetInt32(nodePortDatumArray[index]);
		text *commandText = DatumGetTextP(commandStringDatumArray[index]);
		char *commandString = text_to_cstring(commandText);

		nodeNames[index] = makeStringInfo();
		commandStrings[index] = makeStringInfo();

		appendStringInfo(nodeNames[index], "%s", nodeName);
		nodePorts[index] = nodePort;
		appendStringInfo(commandStrings[index], "%s", commandString);
	}

	*nodeNameArray = nodeNames;
	*nodePortsArray = nodePorts;
	*commandStringArray = commandStrings;
	*parallel = parallelExecution;

	return nodeNameCount;
}