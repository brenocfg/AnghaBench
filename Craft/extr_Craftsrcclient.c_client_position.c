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
 int /*<<< orphan*/  client_enabled ; 
 int /*<<< orphan*/  client_send (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,float,float,float,float,float) ; 

void client_position(float x, float y, float z, float rx, float ry) {
    if (!client_enabled) {
        return;
    }
    static float px, py, pz, prx, pry = 0;
    float distance =
        (px - x) * (px - x) +
        (py - y) * (py - y) +
        (pz - z) * (pz - z) +
        (prx - rx) * (prx - rx) +
        (pry - ry) * (pry - ry);
    if (distance < 0.0001) {
        return;
    }
    px = x; py = y; pz = z; prx = rx; pry = ry;
    char buffer[1024];
    snprintf(buffer, 1024, "P,%.2f,%.2f,%.2f,%.2f,%.2f\n", x, y, z, rx, ry);
    client_send(buffer);
}