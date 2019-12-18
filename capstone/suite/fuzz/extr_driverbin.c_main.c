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
typedef  int /*<<< orphan*/  uint8_t ;
struct dirent {scalar_t__ d_type; int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_REG ; 
 int /*<<< orphan*/  LLVMFuzzerTestOneInput (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int fread (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 size_t ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 

int main(int argc, char** argv)
{
    FILE * fp;
    uint8_t Data[0x1000];
    size_t Size;
    DIR *d;
    struct dirent *dir;
    int r = 0;

    if (argc != 2) {
        return 1;
    }

    d = opendir(argv[1]);
    if (d == NULL) {
        printf("Invalid directory\n");
        return 2;
    }
    if (chdir(argv[1]) != 0) {
        closedir(d);
        printf("Invalid directory\n");
        return 2;
    }

    while((dir = readdir(d)) != NULL) {
        //opens the file, get its size, and reads it into a buffer
        if (dir->d_type != DT_REG) {
            continue;
        }
        //printf("Running %s\n", dir->d_name);
        fp = fopen(dir->d_name, "rb");
        if (fp == NULL) {
            r = 3;
            break;
        }
        if (fseek(fp, 0L, SEEK_END) != 0) {
            fclose(fp);
            r = 4;
            break;
        }
        Size = ftell(fp);
        if (Size == (size_t) -1) {
            fclose(fp);
            r = 5;
            break;
        } else if (Size > 0x1000) {
            fclose(fp);
            continue;
        }
        if (fseek(fp, 0L, SEEK_SET) != 0) {
            fclose(fp);
            r = 7;
            break;
        }
        if (fread(Data, Size, 1, fp) != 1) {
            fclose(fp);
            r = 8;
            break;
        }

        //lauch fuzzer
        LLVMFuzzerTestOneInput(Data, Size);
        fclose(fp);
    }
    closedir(d);
    return r;
}