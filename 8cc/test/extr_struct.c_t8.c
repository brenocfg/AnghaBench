__attribute__((used)) static void t8() {
    struct tag8 { int a; int b; } x;
    struct tag8 *p = &x;
    (*p).b = 72;
    expect(72, x.b);
}