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

/* Variables and functions */
 int /*<<< orphan*/  leftShift1 (char*,int) ; 
 int /*<<< orphan*/  leftShift2 (char*,int,int) ; 
 int /*<<< orphan*/  leftShift3 (char*,int,int) ; 
 int /*<<< orphan*/  leftShift4 (char*,int,int) ; 
 int /*<<< orphan*/  leftShift5 (char*,int,int) ; 
 int /*<<< orphan*/  leftShift6 (char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 int strlen (char*) ; 

int main()
{
    char str[50];
    sprintf(str, "abcdefghijk");
    printf("The origin str is :%s\tlen is :%zu\n", str, strlen(str));
    printf("\n");
    leftShift1(str, 2);
    printf("The leftShift1 str is :%s\n", str);
    leftShift1(str, -2);
    printf("The leftShift1 str is :%s\n", str);
    leftShift1(str, 3);
    printf("The leftShift1 str is :%s\n", str);
    leftShift1(str, strlen(str) - 3);
    printf("The leftShift1 str is :%s\n", str);
    printf("\n");

    leftShift2(str, strlen(str), 3);
    printf("The leftShift2 str is :%s\n", str);
    leftShift2(str, strlen(str), strlen(str) - 3);
    printf("The leftShift2 str is :%s\n", str);
    leftShift2(str + 2, strlen(str) - 2, 2);
    printf("The leftShift2 str is :%s\n", str);
    leftShift2(str + 2, strlen(str) - 2, strlen(str) - 2 - 2);
    printf("The leftShift2 str is :%s\n", str);
    printf("\n");


    leftShift3(str, strlen(str), 3);
    printf("The leftShift3 str is :%s\n", str);
    leftShift3(str, strlen(str), strlen(str) - 3);
    printf("The leftShift3 str is :%s\n", str);
    leftShift3(str + 2, strlen(str) - 2, 2);
    printf("The leftShift3 str is :%s\n", str);
    leftShift3(str + 2, strlen(str) - 2, strlen(str) - 2 - 2);
    printf("The leftShift3 str is :%s\n", str);
    printf("\n");

    leftShift4(str, strlen(str), 3);
    printf("The leftShift4 str is :%s\n", str);
    leftShift4(str, strlen(str), strlen(str) - 3);
    printf("The leftShift4 str is :%s\n", str);
    leftShift4(str + 2, strlen(str) - 2, 2);
    printf("The leftShift4 str is :%s\n", str);
    leftShift4(str + 2, strlen(str) - 2, strlen(str) - 2 - 2);
    printf("The leftShift4 str is :%s\n", str);
    printf("\n");

    leftShift5(str, strlen(str), 3);
    printf("The leftShift5 str is :%s\n", str);
    leftShift5(str, strlen(str), strlen(str) - 3);
    printf("The leftShift5 str is :%s\n", str);
    leftShift5(str + 2, strlen(str) - 2, 2);
    printf("The leftShift5 str is :%s\n", str);
    leftShift5(str + 2, strlen(str) - 2, strlen(str) - 2 - 2);
    printf("The leftShift5 str is :%s\n", str);
    printf("\n");

    leftShift6(str, strlen(str), 3);
    printf("The leftShift6 str is :%s\n", str);
    leftShift6(str, strlen(str), strlen(str) - 3);
    printf("The leftShift6 str is :%s\n", str);
    leftShift6(str + 2, strlen(str) - 2, 2);
    printf("The leftShift6 str is :%s\n", str);
    leftShift6(str + 2, strlen(str) - 2, strlen(str) - 2 - 2);
    printf("The leftShift6 str is :%s\n", str);
    printf("\n");

    return 0;
}