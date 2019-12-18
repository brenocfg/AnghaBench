#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
typedef  int int16 ;
struct TYPE_9__ {int /*<<< orphan*/  es_query_cxt; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ps_ExprContext; } ;
typedef  TYPE_1__ PlanState ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  int /*<<< orphan*/  ExprContext ;
typedef  int /*<<< orphan*/  Expr ;
typedef  TYPE_2__ EState ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 TYPE_2__* CreateExecutorState () ; 
 int /*<<< orphan*/  ExecEvalExprSwitchContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * ExecInitExpr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  FreeExecutorState (TYPE_2__*) ; 
 int /*<<< orphan*/ * GetPerTupleExprContext (TYPE_2__*) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_DETOAST_DATUM_COPY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  datumCopy (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fix_opfuncids (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_typlenbyval (int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ makeConst (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static Expr *
citus_evaluate_expr(Expr *expr, Oid result_type, int32 result_typmod,
					Oid result_collation, PlanState *planState)
{
	EState     *estate;
	ExprState  *exprstate;
	ExprContext *econtext;
	MemoryContext oldcontext;
	Datum		const_val;
	bool		const_is_null;
	int16		resultTypLen;
	bool		resultTypByVal;

	/*
	 * To use the executor, we need an EState.
	 */
	estate = CreateExecutorState();

	/* We can use the estate's working context to avoid memory leaks. */
	oldcontext = MemoryContextSwitchTo(estate->es_query_cxt);

	/* Make sure any opfuncids are filled in. */
	fix_opfuncids((Node *) expr);

	/*
	 * Prepare expr for execution.  (Note: we can't use ExecPrepareExpr
	 * because it'd result in recursively invoking eval_const_expressions.)
	 */
	exprstate = ExecInitExpr(expr, planState);

	if (planState != NULL)
	{
		/* use executor's context to pass down parameters */
		econtext = planState->ps_ExprContext;
	}
	else
	{
		/* when called from a function, use a default context */
		econtext = GetPerTupleExprContext(estate);
	}

	/*
	 * And evaluate it.
	 */
	const_val = ExecEvalExprSwitchContext(exprstate, econtext, &const_is_null);

	/* Get info needed about result datatype */
	get_typlenbyval(result_type, &resultTypLen, &resultTypByVal);

	/* Get back to outer memory context */
	MemoryContextSwitchTo(oldcontext);

	/*
	 * Must copy result out of sub-context used by expression eval.
	 *
	 * Also, if it's varlena, forcibly detoast it.  This protects us against
	 * storing TOAST pointers into plans that might outlive the referenced
	 * data.  (makeConst would handle detoasting anyway, but it's worth a few
	 * extra lines here so that we can do the copy and detoast in one step.)
	 */
	if (!const_is_null)
	{
		if (resultTypLen == -1)
			const_val = PointerGetDatum(PG_DETOAST_DATUM_COPY(const_val));
		else
			const_val = datumCopy(const_val, resultTypByVal, resultTypLen);
	}

	/* Release all the junk we just created */
	FreeExecutorState(estate);

	/*
	 * Make the constant result node.
	 */
	return (Expr *) makeConst(result_type, result_typmod, result_collation,
							  resultTypLen,
							  const_val, const_is_null,
							  resultTypByVal);
}