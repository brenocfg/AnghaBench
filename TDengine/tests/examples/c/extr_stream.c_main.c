#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sql ;
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_5__ {char* server_ip; char* db_name; char* tbl_name; } ;
typedef  TYPE_1__ param ;
typedef  int /*<<< orphan*/  TAOS_STREAM ;
typedef  int /*<<< orphan*/  TAOS ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int g_thread_exit_flag ; 
 int /*<<< orphan*/  getchar () ; 
 scalar_t__ insert_rows ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void* (*) (void*),TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  streamCallBack ; 
 int /*<<< orphan*/  taos_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taos_close_stream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * taos_connect (char*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taos_init () ; 
 int /*<<< orphan*/ * taos_open_stream (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int main(int argc, char *argv[]) 
{
  TAOS       *taos;
  char        db_name[64];
  char        tbl_name[64];
  char        sql[1024] = { 0 };

  if (argc != 4) {
    printf("usage: %s server-ip dbname tblname\n", argv[0]);
    exit(0);
  } 

  // init TAOS
  taos_init();

  strcpy(db_name, argv[2]);
  strcpy(tbl_name, argv[3]);
  
  // create pthread to insert into row per second for stream calc
  param *t_param = (param *)malloc(sizeof(param));
  if (NULL == t_param)
  {
    printf("failed to malloc\n");
    exit(1);
  }
  memset(t_param, 0, sizeof(param)); 
  strcpy(t_param->server_ip, argv[1]);
  strcpy(t_param->db_name, db_name);
  strcpy(t_param->tbl_name, tbl_name);

  pthread_t pid;
  pthread_create(&pid, NULL, (void * (*)(void *))insert_rows, t_param);

  sleep(3); // waiting for database is created.
  // open connection to database
  taos = taos_connect(argv[1], "root", "taosdata", db_name, 0);
  if (taos == NULL) {
    printf("failed to connet to server:%s\n", argv[1]);
	  free(t_param);
    exit(1);
  }

  // starting stream calc, 
  printf("please input stream SQL:[e.g., select count(*) from tblname interval(5s) sliding(2s);]\n");
  fgets(sql, sizeof(sql), stdin);
  if (sql[0] == 0) {
    printf("input NULL stream SQL, so exit!\n");	
    free(t_param);
    exit(1);
  }

  // param is set to NULL in this demo, it shall be set to the pointer to app context 
  TAOS_STREAM *pStream = taos_open_stream(taos, sql, streamCallBack, 0, NULL, NULL);
  if (NULL == pStream) {
    printf("failed to create stream\n");	
    free(t_param);
    exit(1);
  }
  
  printf("presss any key to exit\n");
  getchar();

  taos_close_stream(pStream);
  
  g_thread_exit_flag = 1;  
  pthread_join(pid, NULL);

  taos_close(taos);
  free(t_param); 

  return 0;
}