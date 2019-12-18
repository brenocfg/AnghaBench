#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int is_cf; } ;

/* Variables and functions */
 int FALSE ; 
 int IDE_debug ; 
 int IDE_enabled ; 
 int /*<<< orphan*/  Log_print (char*,...) ; 
 int TRUE ; 
 char* Util_strdup (char*) ; 
 TYPE_1__ device ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int ide_init_drive (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int IDE_Initialise(int *argc, char *argv[]) {
    int i, j, ret = TRUE;
    char *filename = NULL;

    if (IDE_debug)
        fprintf(stderr, "ide: init\n");

    for (i = j = 1; i < *argc; i++) {
        int available = i + 1 < *argc;

        if (!strcmp(argv[i], "-ide"  )) {
            if (!available) {
                Log_print("Missing argument for '%s'", argv[i]);
                return FALSE;
            }
            filename = Util_strdup(argv[++i]);
        } else if (!strcmp(argv[i], "-ide_debug")) {
            IDE_debug = 1;
        } else if (!strcmp(argv[i], "-ide_cf")) {
            device.is_cf = 1;
        } else {
             if (!strcmp(argv[i], "-help")) {
                 Log_print("\t-ide <file>      Enable IDE emulation");
                 Log_print("\t-ide_debug       Enable IDE Debug Output");
                 Log_print("\t-ide_cf          Enable CF emulation");
             }
             argv[j++] = argv[i];
        }
    }
    *argc = j;

    if (filename) {
        IDE_enabled = ret = ide_init_drive(&device, filename);
        free(filename);
    }

    return ret;
}