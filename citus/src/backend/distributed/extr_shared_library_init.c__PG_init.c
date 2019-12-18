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

/* Variables and functions */
 int /*<<< orphan*/ * CitusExecutorRun ; 
 int /*<<< orphan*/ * CitusExecutorStart ; 
 int /*<<< orphan*/  CreateRequiredDirectories () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * ExecutorRun_hook ; 
 int /*<<< orphan*/ * ExecutorStart_hook ; 
 int /*<<< orphan*/  InitConnParams () ; 
 int /*<<< orphan*/  InitPlacementConnectionManagement () ; 
 int /*<<< orphan*/  InitializeBackendManagement () ; 
 int /*<<< orphan*/  InitializeCitusQueryStats () ; 
 int /*<<< orphan*/  InitializeConnectionManagement () ; 
 int /*<<< orphan*/  InitializeMaintenanceDaemon () ; 
 int /*<<< orphan*/  InitializeTransactionManagement () ; 
 scalar_t__ IsBinaryUpgrade ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int /*<<< orphan*/  PGC_POSTMASTER ; 
 int /*<<< orphan*/  PGC_S_OVERRIDE ; 
 int /*<<< orphan*/ * ProcessUtility_hook ; 
 int /*<<< orphan*/  RegisterCitusConfigVariables () ; 
 int /*<<< orphan*/  RegisterCitusCustomScanMethods () ; 
 int /*<<< orphan*/  RegisterNodes () ; 
 int /*<<< orphan*/  ResizeStackToMaximumDepth () ; 
 int /*<<< orphan*/  SetConfigOption (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TaskTrackerRegister () ; 
 int /*<<< orphan*/ * distributed_planner ; 
 int /*<<< orphan*/  emit_log_hook ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/ * multi_ProcessUtility ; 
 int /*<<< orphan*/  multi_join_restriction_hook ; 
 int /*<<< orphan*/  multi_log_hook ; 
 int /*<<< orphan*/  multi_relation_restriction_hook ; 
 int /*<<< orphan*/ * planner_hook ; 
 int /*<<< orphan*/  process_shared_preload_libraries_in_progress ; 
 int /*<<< orphan*/  set_join_pathlist_hook ; 
 int /*<<< orphan*/  set_rel_pathlist_hook ; 

void
_PG_init(void)
{
	if (!process_shared_preload_libraries_in_progress)
	{
		ereport(ERROR, (errmsg("Citus can only be loaded via shared_preload_libraries"),
						errhint("Add citus to shared_preload_libraries configuration "
								"variable in postgresql.conf in master and workers. Note "
								"that citus should be at the beginning of "
								"shared_preload_libraries.")));
	}

	/*
	 * Perform checks before registering any hooks, to avoid erroring out in a
	 * partial state.
	 *
	 * In many cases (e.g. planner and utility hook, to run inside
	 * pg_stat_statements et. al.) we have to be loaded before other hooks
	 * (thus as the innermost/last running hook) to be able to do our
	 * duties. For simplicity insist that all hooks are previously unused.
	 */
	if (planner_hook != NULL || ProcessUtility_hook != NULL ||
		ExecutorStart_hook != NULL || ExecutorRun_hook != NULL)
	{
		ereport(ERROR, (errmsg("Citus has to be loaded first"),
						errhint("Place citus at the beginning of "
								"shared_preload_libraries.")));
	}

	ResizeStackToMaximumDepth();

	/*
	 * Extend the database directory structure before continuing with
	 * initialization - one of the later steps might require them to exist.
	 * If in a sub-process (windows / EXEC_BACKEND) this already has been
	 * done.
	 */
	if (!IsUnderPostmaster)
	{
		CreateRequiredDirectories();
	}

	InitConnParams();

	/*
	 * Register Citus configuration variables. Do so before intercepting
	 * hooks or calling initialization functions, in case we want to do the
	 * latter in a configuration dependent manner.
	 */
	RegisterCitusConfigVariables();

	/* make our additional node types known */
	RegisterNodes();

	/* make our custom scan nodes known */
	RegisterCitusCustomScanMethods();

	/* intercept planner */
	planner_hook = distributed_planner;

	/* register utility hook */
	ProcessUtility_hook = multi_ProcessUtility;

	/* register for planner hook */
	set_rel_pathlist_hook = multi_relation_restriction_hook;
	set_join_pathlist_hook = multi_join_restriction_hook;
	ExecutorStart_hook = CitusExecutorStart;
	ExecutorRun_hook = CitusExecutorRun;

	/* register hook for error messages */
	emit_log_hook = multi_log_hook;

	InitializeMaintenanceDaemon();

	/* organize that task tracker is started once server is up */
	TaskTrackerRegister();

	/* initialize coordinated transaction management */
	InitializeTransactionManagement();
	InitializeBackendManagement();
	InitializeConnectionManagement();
	InitPlacementConnectionManagement();
	InitializeCitusQueryStats();

	/* enable modification of pg_catalog tables during pg_upgrade */
	if (IsBinaryUpgrade)
	{
		SetConfigOption("allow_system_table_mods", "true", PGC_POSTMASTER,
						PGC_S_OVERRIDE);
	}
}