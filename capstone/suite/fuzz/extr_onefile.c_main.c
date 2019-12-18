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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LLVMFuzzerTestOneInput (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 size_t ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 

int main(int argc, char** argv)
{
    FILE * fp;
    uint8_t *Data;
    size_t Size;

    if (argc != 2) {
        return 1;
    }
    //opens the file, get its size, and reads it into a buffer
    fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        return 2;
    }
    if (fseek(fp, 0L, SEEK_END) != 0) {
        fclose(fp);
        return 2;
    }
    Size = ftell(fp);
    if (Size == (size_t) -1) {
        fclose(fp);
        return 2;
    }
    if (fseek(fp, 0L, SEEK_SET) != 0) {
        fclose(fp);
        return 2;
    }
    Data = malloc(Size);
    if (Data == NULL) {
        fclose(fp);
        return 2;
    }
    if (fread(Data, Size, 1, fp) != 1) {
        fclose(fp);
        free(Data);
        return 2;
    }

    //lauch fuzzer
    LLVMFuzzerTestOneInput(Data, Size);
    free(Data);
    fclose(fp);
    return 0;
}