#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char* sds ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {char* eval; int /*<<< orphan*/  repeat; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int cliSendCommand (int,char**,int /*<<< orphan*/ ) ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 char* sdscatlen (char*,char*,size_t) ; 
 char* sdscatprintf (char*,char*,int) ; 
 char* sdsempty () ; 
 char* sdsnew (char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 char** zmalloc (int) ; 

__attribute__((used)) static int evalMode(int argc, char **argv) {
    sds script = sdsempty();
    FILE *fp;
    char buf[1024];
    size_t nread;
    char **argv2;
    int j, got_comma = 0, keys = 0;

    /* Load the script from the file, as an sds string. */
    fp = fopen(config.eval,"r");
    if (!fp) {
        fprintf(stderr,
            "Can't open file '%s': %s\n", config.eval, strerror(errno));
        exit(1);
    }
    while((nread = fread(buf,1,sizeof(buf),fp)) != 0) {
        script = sdscatlen(script,buf,nread);
    }
    fclose(fp);

    /* Create our argument vector */
    argv2 = zmalloc(sizeof(sds)*(argc+3));
    argv2[0] = sdsnew("EVAL");
    argv2[1] = script;
    for (j = 0; j < argc; j++) {
        if (!got_comma && argv[j][0] == ',' && argv[j][1] == 0) {
            got_comma = 1;
            continue;
        }
        argv2[j+3-got_comma] = sdsnew(argv[j]);
        if (!got_comma) keys++;
    }
    argv2[2] = sdscatprintf(sdsempty(),"%d",keys);

    /* Call it */
    return cliSendCommand(argc+3-got_comma, argv2, config.repeat);
}