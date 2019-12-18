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
 int /*<<< orphan*/  many_floats (double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double) ; 
 int /*<<< orphan*/  many_ints (int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  mixed (double,int,double,int,double,int,double,int,double,int,double,int,double,int,double,int,double,int,double,int,double,int,double,int,double,int,double,int,double,int,double,int,double,int,double,int,double,int,double,int) ; 
 int /*<<< orphan*/  print (char*) ; 

void testmain() {
    print("function argument");

    many_ints(1, 2, 3, 4, 5, 6, 7, 8, 9);

    many_floats(1.0, 2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,
                9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                17.0);

    mixed(1.0,  2,  3.0,  4,  5.0,  6,  7.0,  8,  9.0,  10,
          11.0, 12, 13.0, 14, 15.0, 16, 17.0, 18, 19.0, 20,
          21.0, 22, 23.0, 24, 25.0, 26, 27.0, 28, 29.0, 30,
          31.0, 32, 33.0, 34, 35.0, 36, 37.0, 38, 39.0, 40);
}