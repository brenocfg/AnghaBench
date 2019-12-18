__attribute__((used)) static void t5() {
    struct tag5 { int a; } x;
    struct tag5 *p = &x;
    x.a = 68;
    expect(68, (*p).a);
}