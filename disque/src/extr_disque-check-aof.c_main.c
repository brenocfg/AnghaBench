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
struct disque_stat {scalar_t__ st_size; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int disque_fstat (int /*<<< orphan*/ ,struct disque_stat*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int ftruncate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ process (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

int main(int argc, char **argv) {
    char *filename;
    int fix = 0;

    if (argc < 2) {
        printf("Usage: %s [--fix] <file.aof>\n", argv[0]);
        exit(1);
    } else if (argc == 2) {
        filename = argv[1];
    } else if (argc == 3) {
        if (strcmp(argv[1],"--fix") != 0) {
            printf("Invalid argument: %s\n", argv[1]);
            exit(1);
        }
        filename = argv[2];
        fix = 1;
    } else {
        printf("Invalid arguments\n");
        exit(1);
    }

    FILE *fp = fopen(filename,"r+");
    if (fp == NULL) {
        printf("Cannot open file: %s\n", filename);
        exit(1);
    }

    struct disque_stat sb;
    if (disque_fstat(fileno(fp),&sb) == -1) {
        printf("Cannot stat file: %s\n", filename);
        exit(1);
    }

    off_t size = sb.st_size;
    if (size == 0) {
        printf("Empty file: %s\n", filename);
        exit(1);
    }

    off_t pos = process(fp);
    off_t diff = size-pos;
    printf("AOF analyzed: size=%lld, ok_up_to=%lld, diff=%lld\n",
        (long long) size, (long long) pos, (long long) diff);
    if (diff > 0) {
        if (fix) {
            char buf[2];
            printf("This will shrink the AOF from %lld bytes, with %lld bytes, to %lld bytes\n",(long long)size,(long long)diff,(long long)pos);
            printf("Continue? [y/N]: ");
            if (fgets(buf,sizeof(buf),stdin) == NULL ||
                strncasecmp(buf,"y",1) != 0) {
                    printf("Aborting...\n");
                    exit(1);
            }
            if (ftruncate(fileno(fp), pos) == -1) {
                printf("Failed to truncate AOF\n");
                exit(1);
            } else {
                printf("Successfully truncated AOF\n");
            }
        } else {
            printf("AOF is not valid\n");
            exit(1);
        }
    } else {
        printf("AOF is valid\n");
    }

    fclose(fp);
    return 0;
}