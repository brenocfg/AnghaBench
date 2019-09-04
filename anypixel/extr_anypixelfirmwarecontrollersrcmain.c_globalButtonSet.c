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
#define  PANEL_NE 131 
#define  PANEL_NW 130 
#define  PANEL_SE 129 
#define  PANEL_SW 128 
 int* buttonpacket ; 

void globalButtonSet(int boardButtonIndex, int value, int panel) {
    int col = boardButtonIndex % 7;
    int row = boardButtonIndex / 7;
    int bitAddr;

    switch(panel) {
        case PANEL_NW:
            bitAddr = row * 14 + col;
            break;
        case PANEL_NE:
            bitAddr = row * 14 + col + 7;
            break;
        case PANEL_SW:
            bitAddr = (row + 7) * 14 + col;
            break;
        case PANEL_SE:
            bitAddr = (row + 7) * 14 + col + 7;
            break;
    }
    int byteAddr = bitAddr / 8;
    int bitOffset = 7-(bitAddr - (byteAddr*8));

    if(value)
        buttonpacket[4+byteAddr] |= (1 << bitOffset);
    else
        buttonpacket[4+byteAddr] &= ~(1 << bitOffset);
}