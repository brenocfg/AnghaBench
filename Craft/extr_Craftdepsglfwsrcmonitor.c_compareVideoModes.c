#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int redBits; int greenBits; int blueBits; int width; int height; int refreshRate; } ;
typedef  TYPE_1__ GLFWvidmode ;

/* Variables and functions */

__attribute__((used)) static int compareVideoModes(const void* firstPtr, const void* secondPtr)
{
    int firstBPP, secondBPP, firstSize, secondSize;
    const GLFWvidmode* first = firstPtr;
    const GLFWvidmode* second = secondPtr;

    // First sort on color bits per pixel
    firstBPP = first->redBits + first->greenBits + first->blueBits;
    secondBPP = second->redBits + second->greenBits + second->blueBits;
    if (firstBPP != secondBPP)
        return firstBPP - secondBPP;

    // Then sort on screen area, in pixels
    firstSize = first->width * first->height;
    secondSize = second->width * second->height;
    if (firstSize != secondSize)
        return firstSize - secondSize;

    // Lastly sort on refresh rate
    return first->refreshRate - second->refreshRate;
}