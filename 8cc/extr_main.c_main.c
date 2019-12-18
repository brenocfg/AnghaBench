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
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  Vector ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  asmfile ; 
 scalar_t__ atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_body (int /*<<< orphan*/ ) ; 
 scalar_t__ buf_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_output_file () ; 
 int /*<<< orphan*/  cpp_init () ; 
 int /*<<< orphan*/  cppdefs ; 
 scalar_t__ cpponly ; 
 int /*<<< orphan*/  delete_temp_files ; 
 int /*<<< orphan*/  dumpasm ; 
 scalar_t__ dumpast ; 
 int /*<<< orphan*/  emit_toplevel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  execlp (char*,char*,char*,scalar_t__,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  infile ; 
 int /*<<< orphan*/  lex_init (int /*<<< orphan*/ ) ; 
 char* node2s (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_asmfile () ; 
 scalar_t__ outfile ; 
 int /*<<< orphan*/  parse_init () ; 
 int /*<<< orphan*/  parseopt (int,char**) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  preprocess () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  read_from_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * read_toplevels () ; 
 scalar_t__ replace_suffix (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  set_output_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/ * vec_get (int /*<<< orphan*/ *,int) ; 
 int vec_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv) {
    setbuf(stdout, NULL);
    if (atexit(delete_temp_files))
        perror("atexit");
    parseopt(argc, argv);
    lex_init(infile);
    cpp_init();
    parse_init();
    set_output_file(open_asmfile());
    if (buf_len(cppdefs) > 0)
        read_from_string(buf_body(cppdefs));

    if (cpponly)
        preprocess();

    Vector *toplevels = read_toplevels();
    for (int i = 0; i < vec_len(toplevels); i++) {
        Node *v = vec_get(toplevels, i);
        if (dumpast)
            printf("%s", node2s(v));
        else
            emit_toplevel(v);
    }

    close_output_file();

    if (!dumpast && !dumpasm) {
        if (!outfile)
            outfile = replace_suffix(base(infile), 'o');
        pid_t pid = fork();
        if (pid < 0) perror("fork");
        if (pid == 0) {
            execlp("as", "as", "-o", outfile, "-c", asmfile, (char *)NULL);
            perror("execl failed");
        }
        int status;
        waitpid(pid, &status, 0);
        if (status < 0)
            error("as failed");
    }
    return 0;
}