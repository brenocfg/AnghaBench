#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mpc_status ;
struct TYPE_7__ {int file_size; int /*<<< orphan*/ * p_file; int /*<<< orphan*/  tell; int /*<<< orphan*/  seek; int /*<<< orphan*/  read; int /*<<< orphan*/  get_size; int /*<<< orphan*/  canseek; struct TYPE_7__* data; int /*<<< orphan*/  is_seekable; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ mpc_reader_stdio ;
typedef  TYPE_1__ mpc_reader ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MPC_STATUS_FAIL ; 
 int /*<<< orphan*/  MPC_STATUS_OK ; 
 int /*<<< orphan*/  MPC_TRUE ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  STDIO_MAGIC ; 
 int /*<<< orphan*/  canseek_stdio ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_size_stdio ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_stdio ; 
 int /*<<< orphan*/  seek_stdio ; 
 int /*<<< orphan*/  tell_stdio ; 

mpc_status
mpc_reader_init_stdio_stream(mpc_reader * p_reader, FILE * p_file)
{
    mpc_reader tmp_reader; mpc_reader_stdio *p_stdio; int err;

    p_stdio = NULL;
    memset(&tmp_reader, 0, sizeof tmp_reader);
    p_stdio = malloc(sizeof *p_stdio);
    if(!p_stdio) return MPC_STATUS_FAIL;
    memset(p_stdio, 0, sizeof *p_stdio);

    p_stdio->magic  = STDIO_MAGIC;
    p_stdio->p_file = p_file;
    p_stdio->is_seekable = MPC_TRUE;
    err = fseek(p_stdio->p_file, 0, SEEK_END);
    if(err < 0) goto clean;
    err = ftell(p_stdio->p_file);
    if(err < 0) goto clean;
    p_stdio->file_size = err;
    err = fseek(p_stdio->p_file, 0, SEEK_SET);
    if(err < 0) goto clean;

    tmp_reader.data     = p_stdio;
    tmp_reader.canseek  = canseek_stdio;
    tmp_reader.get_size = get_size_stdio;
    tmp_reader.read     = read_stdio;
    tmp_reader.seek     = seek_stdio;
    tmp_reader.tell     = tell_stdio;

    *p_reader = tmp_reader;
    return MPC_STATUS_OK;
clean:
    if(p_stdio && p_stdio->p_file)
        fclose(p_stdio->p_file);
    free(p_stdio);
    return MPC_STATUS_FAIL;
}