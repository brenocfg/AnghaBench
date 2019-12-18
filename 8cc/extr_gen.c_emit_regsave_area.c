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
 int REGAREA_SIZE ; 
 int /*<<< orphan*/  emit (char*,...) ; 

__attribute__((used)) static int emit_regsave_area() {
    emit("sub $%d, #rsp", REGAREA_SIZE);
    emit("mov #rdi, (#rsp)");
    emit("mov #rsi, 8(#rsp)");
    emit("mov #rdx, 16(#rsp)");
    emit("mov #rcx, 24(#rsp)");
    emit("mov #r8, 32(#rsp)");
    emit("mov #r9, 40(#rsp)");
    emit("movaps #xmm0, 48(#rsp)");
    emit("movaps #xmm1, 64(#rsp)");
    emit("movaps #xmm2, 80(#rsp)");
    emit("movaps #xmm3, 96(#rsp)");
    emit("movaps #xmm4, 112(#rsp)");
    emit("movaps #xmm5, 128(#rsp)");
    emit("movaps #xmm6, 144(#rsp)");
    emit("movaps #xmm7, 160(#rsp)");
    return REGAREA_SIZE;
}