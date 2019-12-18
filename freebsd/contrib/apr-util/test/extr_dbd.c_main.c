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
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_dbd_t ;
typedef  int /*<<< orphan*/  apr_dbd_driver_t ;

/* Variables and functions */
#define  APR_EDSOOPEN 132 
#define  APR_EGENERAL 131 
#define  APR_ENOTIMPL 130 
#define  APR_ESYMNOTFOUND 129 
#define  APR_SUCCESS 128 
 int /*<<< orphan*/  TEST (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_dbd_close (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int apr_dbd_get_driver (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  apr_dbd_init (int /*<<< orphan*/ *) ; 
 int apr_dbd_open (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  apr_initialize () ; 
 int /*<<< orphan*/  apr_pool_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_terminate () ; 
 int /*<<< orphan*/  create_table ; 
 int /*<<< orphan*/  drop_table ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  insert_rows ; 
 int /*<<< orphan*/  invalid_op ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 int /*<<< orphan*/  select_random ; 
 int /*<<< orphan*/  select_sequential ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  test_pquery ; 
 int /*<<< orphan*/  test_pselect ; 
 int /*<<< orphan*/  test_transactions ; 

int main(int argc, char** argv)
{
    const char *name;
    const char *params;
    apr_pool_t *pool = NULL;
    apr_dbd_t *sql = NULL;
    const apr_dbd_driver_t *driver = NULL;
    int rv;

    apr_initialize();
    apr_pool_create(&pool, NULL);

    if (argc >= 2 && argc <= 3) {
        name = argv[1];
        params = ( argc == 3 ) ? argv[2] : "";
        apr_dbd_init(pool);
        setbuf(stdout,NULL);
        rv = apr_dbd_get_driver(pool, name, &driver);
        switch (rv) {
        case APR_SUCCESS:
           printf("Loaded %s driver OK.\n", name);
           break;
        case APR_EDSOOPEN:
           printf("Failed to load driver file apr_dbd_%s.so\n", name);
           goto finish;
        case APR_ESYMNOTFOUND:
           printf("Failed to load driver apr_dbd_%s_driver.\n", name);
           goto finish;
        case APR_ENOTIMPL:
           printf("No driver available for %s.\n", name);
           goto finish;
        default:        /* it's a bug if none of the above happen */
           printf("Internal error loading %s.\n", name);
           goto finish;
        }
        rv = apr_dbd_open(driver, pool, params, &sql);
        switch (rv) {
        case APR_SUCCESS:
           printf("Opened %s[%s] OK\n", name, params);
           break;
        case APR_EGENERAL:
           printf("Failed to open %s[%s]\n", name, params);
           goto finish;
        default:        /* it's a bug if none of the above happen */
           printf("Internal error opening %s[%s]\n", name, params);
           goto finish;
        }
        TEST("create table", create_table);
        TEST("insert rows", insert_rows);
        TEST("invalid op", invalid_op);
        TEST("select random", select_random);
        TEST("select sequential", select_sequential);
        TEST("transactions", test_transactions);
        TEST("prepared select", test_pselect);
        TEST("prepared query", test_pquery);
        TEST("drop table", drop_table);
        apr_dbd_close(driver, sql);
    }
    else {
        fprintf(stderr, "Usage: %s driver-name [params]\n", argv[0]);
    }
finish:
    apr_pool_destroy(pool);
    apr_terminate();
    return 0;
}