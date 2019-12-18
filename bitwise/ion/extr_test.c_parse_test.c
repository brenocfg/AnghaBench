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
typedef  int /*<<< orphan*/  decls ;

/* Variables and functions */
 int /*<<< orphan*/  init_stream (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  printf (char*) ; 

void parse_test(void) {
    const char *decls[] = {
        "var x: char[256] = {1, 2, 3, ['a'] = 4}",
        "struct Vector { x, y: float; }",
        "var v = Vector{x = 1.0, y = -1.0}",
        "var v: Vector = {1.0, -1.0}",
        "const n = sizeof(:int*[16])",
        "const n = sizeof(1+2)",
        "var x = b == 1 ? 1+2 : 3-4",
        "func fact(n: int): int { trace(\"fact\"); if (n == 0) { return 1; } else { return n * fact(n-1); } }",
        "func fact(n: int): int { p := 1; for (i := 1; i <= n; i++) { p *= i; } return p; }",
        "var foo = a ? a&b + c<<d + e*f == +u-v-w + *g/h(x,y) + -i%k[x] && m <= n*(p+q)/r : 0",
        "func f(x: int): bool { switch (x) { case 0: case 1: return true; case 2: default: return false; } }",
        "enum Color { RED = 3, GREEN, BLUE = 0 }",
        "const pi = 3.14",
        "union IntOrFloat { i: int; f: float; }",
        "typedef Vectors = Vector[1+2]",
        "func f() { do { print(42); } while(1); }",
        "typedef T = (func(int):int)[16]",
        "func f() { enum E { A, B, C } return; }",
        "func f() { if (1) { return 1; } else if (2) { return 2; } else { return 3; } }",
};
    for (const char **it = decls; it != decls + sizeof(decls)/sizeof(*decls); it++) {
        init_stream(NULL, *it);
//        Decl *decl = parse_decl();
        printf("\n");
    }
}