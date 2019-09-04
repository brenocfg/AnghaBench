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
struct ColorSystem {double xRed; double yRed; double xGreen; double yGreen; double xBlue; double yBlue; double xWhite; double yWhite; } ;

/* Variables and functions */
 int /*<<< orphan*/  invert_matrix3x3 (double**,double**) ; 

__attribute__((used)) static void get_rgb2xyz_matrix(struct ColorSystem system, double m[3][3])
{
    double S[3], X[4], Z[4];
    int i;

    X[0] = system.xRed   / system.yRed;
    X[1] = system.xGreen / system.yGreen;
    X[2] = system.xBlue  / system.yBlue;
    X[3] = system.xWhite / system.yWhite;

    Z[0] = (1 - system.xRed   - system.yRed)   / system.yRed;
    Z[1] = (1 - system.xGreen - system.yGreen) / system.yGreen;
    Z[2] = (1 - system.xBlue  - system.yBlue)  / system.yBlue;
    Z[3] = (1 - system.xWhite - system.yWhite) / system.yWhite;

    for (i = 0; i < 3; i++) {
        m[0][i] = X[i];
        m[1][i] = 1;
        m[2][i] = Z[i];
    }

    invert_matrix3x3(m, m);

    for (i = 0; i < 3; i++)
        S[i] = m[i][0] * X[3] + m[i][1] * 1 + m[i][2] * Z[3];

    for (i = 0; i < 3; i++) {
        m[0][i] = S[i] * X[i];
        m[1][i] = S[i] * 1;
        m[2][i] = S[i] * Z[i];
    }
}