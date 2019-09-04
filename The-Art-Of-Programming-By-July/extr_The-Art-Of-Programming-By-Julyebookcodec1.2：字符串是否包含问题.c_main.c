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
 scalar_t__ contain1 (char*,char*) ; 
 scalar_t__ contain2 (char*,char*) ; 
 scalar_t__ contain3 (char*,char*) ; 
 scalar_t__ contain4 (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

int main()
{
    char stra[50];
    char strb[50];
    char strc[50];
    sprintf(stra, "ABCDEFGHLMNOPQRS");
    sprintf(strb, "DCGSRQPO");
    sprintf(strc, "DCGSRQPZ");

    if (contain1(stra, strb))
        printf("%s contain %s\n", stra, strb);
    else
        printf("%s not contain %s\n", stra, strb);

    if (contain1(stra, strc))
        printf("%s contain %s\n", stra, strc);
    else
        printf("%s not contain %s\n", stra, strc);

    printf("\n");

    if (contain2(stra, strb))
        printf("%s contain %s\n", stra, strb);
    else
        printf("%s not contain %s\n", stra, strb);

    if (contain2(stra, strc))
        printf("%s contain %s\n", stra, strc);
    else
        printf("%s not contain %s\n", stra, strc);

    printf("\n");

    if (contain3(stra, strb))
        printf("%s contain %s\n", stra, strb);
    else
        printf("%s not contain %s\n", stra, strb);

    if (contain3(stra, strc))
        printf("%s contain %s\n", stra, strc);
    else
        printf("%s not contain %s\n", stra, strc);

    printf("\n");

    if (contain4(stra, strb))
        printf("%s contain %s\n", stra, strb);
    else
        printf("%s not contain %s\n", stra, strb);

    if (contain4(stra, strc))
        printf("%s contain %s\n", stra, strc);
    else
        printf("%s not contain %s\n", stra, strc);

    printf("\n");

    if (contain4("a", "A"))
        printf("a contain A in bit hack method\n");

    /*
     if(contain5("Ab","b")){
     printf("%s contain %s\n",stra,strb);
     }else{
     printf("%s not contain %s\n",stra,strb);
     }
     printf("\n");
     */
    return 0;
}