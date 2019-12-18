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
typedef  char gchar ;

/* Variables and functions */
 int /*<<< orphan*/  START_TIMING (char*,char const*,int) ; 
 int /*<<< orphan*/  STOP_TIMING (char*,char*) ; 
 int /*<<< orphan*/  g_log_set_default_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* getenv_def (char*,char*) ; 
 int /*<<< orphan*/  log_func ; 
 int /*<<< orphan*/  test_server (char const*,int,...) ; 

int main(int argc, char **argv) {
	int rounds;
	const gchar *user;
	const gchar *password;
	const gchar *db;
	const gchar *host;

	user     = getenv_def("MYSQL_TEST_USER", "root");	
	password = getenv_def("MYSQL_TEST_PASSWORD", "");	
	db       = getenv_def("MYSQL_TEST_DB",   "test");	
	host     = getenv_def("MYSQL_TEST_HOST", "127.0.0.1");	

	g_log_set_default_handler(log_func, NULL);
#if 0
	/* warm up */
	START_TIMING("%s:%d", "127.0.0.1", 3306);
	test_server("127.0.0.1", 3306);
	STOP_TIMING("warm-up %s", "done");
#endif
	for (rounds = 0; rounds < 10; rounds++) {
		/* real benchmarks */

		START_TIMING("%s:%d", host, 3306);
		test_server(host, 3306, user, password, db);
		STOP_TIMING("benchmark %s", "done");
	
		START_TIMING("%s:%d", host, 4040);
		test_server(host, 4040, user, password, db);
		STOP_TIMING("benchmark %s", "done");
	}

	return 0;
}