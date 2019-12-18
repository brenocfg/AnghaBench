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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t LINE_SIZE ; 
 int /*<<< orphan*/  SET_NEW_ENV (char*,size_t,char*,char*,...) ; 
 char* calloc (size_t,int) ; 
 int chdir (char*) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 char* dirname (int /*<<< orphan*/ ) ; 
 int errno ; 
 int execvp (char*,char**) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filter ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getenv (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 char* malloc (size_t) ; 
 char* new_gsettings_schema_dir ; 
 char* new_gspath ; 
 char* new_gspath1 ; 
 char* new_ld_library_path ; 
 char* new_path ; 
 char* new_perllib ; 
 char* new_pythonhome ; 
 char* new_pythonpath ; 
 char* new_qt_plugin_path ; 
 char* new_xdg_data_dirs ; 
 int /*<<< orphan*/  putenv (char*) ; 
 int /*<<< orphan*/  realpath (char*,int /*<<< orphan*/ *) ; 
 int scandir (char*,struct dirent***,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int main(int argc, char *argv[]) {
    char *appdir = dirname(realpath("/proc/self/exe", NULL));
    if (!appdir)
        die("Could not access /proc/self/exe\n");

    int ret;
    struct dirent **namelist;
    ret = scandir(appdir, &namelist, filter, NULL);

    if (ret == 0) {
        die("No .desktop files found\n");
    } else if(ret == -1) {
        die("Could not scan directory %s\n", appdir);
    }

    /* Extract executable from .desktop file */
    char *desktop_file = calloc(LINE_SIZE, sizeof(char));
    snprintf(desktop_file, LINE_SIZE, "%s/%s", appdir, namelist[0]->d_name);
    FILE *f     = fopen(desktop_file, "r");
    char *line  = malloc(LINE_SIZE);
    size_t n    = LINE_SIZE;

    do {
        if (getline(&line, &n, f) == -1)
            die("Executable not found, make sure there is a line starting with 'Exec='\n");
    } while(strncmp(line, "Exec=", 5));
    fclose(f);
    char *exe   = line+5;

    // parse arguments
    bool in_quotes = 0;
    for (n = 0; n < LINE_SIZE; n++) {
        if (!line[n])         // end of string
            break;
        else if (line[n] == 10 || line[n] == 13) {
            line[n] = '\0';
            line[n+1] = '\0';
            line[n+2] = '\0';
            break;
        } else if (line[n] == '"') {
            in_quotes = !in_quotes;
        } else if (line[n] == ' ' && !in_quotes)
            line[n] = '\0';
    }

    // count arguments
    char*   arg         = exe;
    int     argcount    = 0;
    while ((arg += (strlen(arg)+1)) && *arg)
        argcount += 1;

    // merge args
    char*   outargptrs[argcount + argc + 1];
    outargptrs[0] = exe;
    int     outargindex = 1;
    arg                 = exe;
    int     argc_       = argc - 1;     // argv[0] is the filename
    char**  argv_       = argv + 1;
    while ((arg += (strlen(arg)+1)) && *arg) {
        if (arg[0] == '%' || (arg[0] == '"' && arg[1] == '%')) {         // handle desktop file field codes
            char code = arg[arg[0] == '%' ? 1 : 2];
            switch(code) {
                case 'f':
                case 'u':
                    if (argc_ > 0) {
                        outargptrs[outargindex++] = *argv_++;
                        argc_--;
                    }
                    break;
                case 'F':
                case 'U':
                    while (argc_ > 0) {
                        outargptrs[outargindex++] = *argv_++;
                        argc_--;
                    }
                    break;
                case 'i':
                case 'c':
                case 'k':
                    fprintf(stderr, "WARNING: Desktop file field code %%%c is not currently supported\n", code);
                    break;
                default:
                    fprintf(stderr, "WARNING: Invalid desktop file field code %%%c\n", code);
                    break;
            }
        } else {
            outargptrs[outargindex++] = arg;
        }
    }
    while (argc_ > 0) {
        outargptrs[outargindex++] = *argv_++;
        argc_--;
    }
    outargptrs[outargindex] = '\0';     // trailing null argument required by execvp()

    // change directory
    size_t appdir_s = strlen(appdir);
    char *usr_in_appdir = malloc(appdir_s + 5);
    snprintf(usr_in_appdir, appdir_s + 5, "%s/usr", appdir);
    ret = chdir(usr_in_appdir);
    if (ret != 0)
        die("Could not cd into %s\n", usr_in_appdir);

    // set environment variables
    char *old_env;
    size_t length;
    const char *format;

    /* https://docs.python.org/2/using/cmdline.html#envvar-PYTHONHOME */
    SET_NEW_ENV(new_pythonhome, appdir_s, "PYTHONHOME=%s/usr/", appdir);

    old_env = getenv("PATH") ?: "";
    SET_NEW_ENV(new_path, appdir_s*5 + strlen(old_env), "PATH=%s/usr/bin/:%s/usr/sbin/:%s/usr/games/:%s/bin/:%s/sbin/:%s", appdir, appdir, appdir, appdir, appdir, old_env);

    old_env = getenv("LD_LIBRARY_PATH") ?: "";
    SET_NEW_ENV(new_ld_library_path, appdir_s*10 + strlen(old_env), "LD_LIBRARY_PATH=%s/usr/lib/:%s/usr/lib/i386-linux-gnu/:%s/usr/lib/x86_64-linux-gnu/:%s/usr/lib32/:%s/usr/lib64/:%s/lib/:%s/lib/i386-linux-gnu/:%s/lib/x86_64-linux-gnu/:%s/lib32/:%s/lib64/:%s", appdir, appdir, appdir, appdir, appdir, appdir, appdir, appdir, appdir, appdir, old_env);

    old_env = getenv("PYTHONPATH") ?: "";
    SET_NEW_ENV(new_pythonpath, appdir_s + strlen(old_env), "PYTHONPATH=%s/usr/share/pyshared/:%s", appdir, old_env);

    old_env = getenv("XDG_DATA_DIRS") ?: "/usr/local/share/:/usr/share/";
    SET_NEW_ENV(new_xdg_data_dirs, appdir_s + strlen(old_env), "XDG_DATA_DIRS=%s/usr/share/:%s", appdir, old_env);

    old_env = getenv("PERLLIB") ?: "";
    SET_NEW_ENV(new_perllib, appdir_s*2 + strlen(old_env), "PERLLIB=%s/usr/share/perl5/:%s/usr/lib/perl5/:%s", appdir, appdir, old_env);

    /* http://askubuntu.com/questions/251712/how-can-i-install-a-gsettings-schema-without-root-privileges */
    old_env = getenv("GSETTINGS_SCHEMA_DIR") ?: "";
    SET_NEW_ENV(new_gsettings_schema_dir, appdir_s + strlen(old_env), "GSETTINGS_SCHEMA_DIR=%s/usr/share/glib-2.0/schemas/:%s", appdir, old_env);

    old_env = getenv("QT_PLUGIN_PATH") ?: "";
    SET_NEW_ENV(new_qt_plugin_path, appdir_s*10 + strlen(old_env), "QT_PLUGIN_PATH=%s/usr/lib/qt4/plugins/:%s/usr/lib/i386-linux-gnu/qt4/plugins/:%s/usr/lib/x86_64-linux-gnu/qt4/plugins/:%s/usr/lib32/qt4/plugins/:%s/usr/lib64/qt4/plugins/:%s/usr/lib/qt5/plugins/:%s/usr/lib/i386-linux-gnu/qt5/plugins/:%s/usr/lib/x86_64-linux-gnu/qt5/plugins/:%s/usr/lib32/qt5/plugins/:%s/usr/lib64/qt5/plugins/:%s", appdir, appdir, appdir, appdir, appdir, appdir, appdir, appdir, appdir, appdir, old_env);

    SET_NEW_ENV(new_gspath, appdir_s + strlen(old_env), "GST_PLUGIN_SYSTEM_PATH=%s/usr/lib/gstreamer:%s", appdir, old_env);
    SET_NEW_ENV(new_gspath1, appdir_s + strlen(old_env), "GST_PLUGIN_SYSTEM_PATH_1_0=%s/usr/lib/gstreamer-1.0:%s", appdir, old_env);
    
    /* Otherwise may get errors because Python cannot write __pycache__ bytecode cache */
    putenv("PYTHONDONTWRITEBYTECODE=1");

    /* Run */
    ret = execvp(exe, outargptrs);

    int error = errno;

    if (ret == -1)
        die("Error executing '%s': %s\n", exe, strerror(error));

    free(line);
    free(desktop_file);
    free(usr_in_appdir);
    free(new_pythonhome);
    free(new_path);
    free(new_ld_library_path);
    free(new_pythonpath);
    free(new_xdg_data_dirs);
    free(new_perllib);
    free(new_gsettings_schema_dir);
    free(new_qt_plugin_path);
    return 0;
}